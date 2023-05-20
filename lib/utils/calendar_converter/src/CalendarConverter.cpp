#include "CalendarConverter.hpp"

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <Wt/WDateTime.h>
#include <Wt/WString.h>

#include "ICharacterReader.hpp"
#include "Calendar.hpp"
#include "Event.hpp"
#include "StringCharacterReader.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

const std::string kDateTimeFormat = "yyyyMMdd'T'hhmmss'Z'";
const std::string kDateFormat = "yyyyMMdd";

std::vector<CalendarSptr> CalendarConverter::IcalendarToCalendar(
    std::unique_ptr<ICharReader>&& char_reader) {
  // установка связей между char_reader, lexer, parser
  IcalendarLexer lexer;
  lexer.set_character_reader(*char_reader);

  IcalendarParser parser;
  parser.set_lexer(lexer);

  // календари, которые будем возвращать
  std::vector<CalendarSptr> calendars;

  // корень AST
  StreamUptr root = parser.Parse();

  // не удалось распарсить или пустой stream
  if (!root || root->components().empty()) {
    return std::vector<CalendarSptr>();
  }

  // проходимся по всем распаршенным календарям
  for (ComponentUptr& component : root->components()) {
    // нас интересуют только календари
    if (component->name() != "VCALENDAR") {
      continue;
    }

    CalendarSptr calendar;
    std::vector<EventSptr> events;

    std::vector<PropertyUptr>& calendar_properties = component->properties();
    for (PropertyUptr& property : calendar_properties) {
      if (property->name() == "X-WR-CALNAME") {
        TextValue* value = dynamic_cast<TextValue*>(property->value().get());
        if (value) {
          calendar->set_summary(std::move(value->text()));
        }
      } else if (property->name() == "X-CALENDULA-DESCRIPTION") {
        TextValue* value = dynamic_cast<TextValue*>(property->value().get());
        if (value) {
          calendar->set_description(std::move(value->text()));
        }
      } else if (property->name() == "X-CALENDULA-COLOR") {
        TextValue* value = dynamic_cast<TextValue*>(property->value().get());
        if (value) {
          calendar->set_color(std::move(value->text()));
        }
      } else if (property->name() == "X-CALENDULA-VISIBILITY") {
        TextValue* value = dynamic_cast<TextValue*>(property->value().get());
        if (value) {
          calendar->set_visibility(std::move(value->text()));
        }
      }
    }

    std::vector<ComponentUptr>& calendar_components = component->components();
    for (ComponentUptr& component : calendar_components) {
      // ищем только события
      if (component->name() != "VEVENT") {
        continue;
      }

      events.push_back(FromIcalendarEvent(component));
    }

    for (EventSptr event : events) {
      // сохранить event в БД
      // добавить event id в calendar->events
    }
    // сохранить calendar в БД

    calendars.push_back(calendar);
  }

  return calendars;
}

EventSptr CalendarConverter::FromIcalendarEvent(
    const ComponentUptr& icalendar_event) {
  EventSptr event;

  std::vector<PropertyUptr>& event_propeties = icalendar_event->properties();

  for (PropertyUptr& property : event_propeties) {
    if (property->name() == "SUMMARY") {
      TextValue* value = dynamic_cast<TextValue*>(property->value().get());
      if (value) {
        event->set_summary(value->text());
      }
    } else if (property->name() == "DESCRIPTION") {
      TextValue* value = dynamic_cast<TextValue*>(property->value().get());
      if (value) {
        event->set_description(value->text());
      }
    } else if (property->name() == "DTSTART") {
      TextValue* value = dynamic_cast<TextValue*>(property->value().get());
      if (value) {
        event->set_start(FromIcalendarDateTime(value->text()));
      }
    } else if (property->name() == "DTEND") {
      TextValue* value = dynamic_cast<TextValue*>(property->value().get());
      if (value) {
        event->set_end(FromIcalendarDateTime(value->text()));
      }
    } else if (property->name() == "RRULE") {
      CompositeValue* composite_value
        = dynamic_cast<CompositeValue*>(property->value().get());
      if (!composite_value) {
        continue;
      }

      event->set_is_reccurent(true);

      for (IValueUptr& value : composite_value->values()) {
        PairValue* pair_value = dynamic_cast<PairValue*>(value.get());
        if (!pair_value) {
          continue;
        }

        if (pair_value->name() == "FREQ") {
          event->set_frequency(pair_value->text());
        } else if (pair_value->name() == "INTERVAL") {
          // TODO(affeeal): проверка на "не число"
          event->set_interval(std::stoul(pair_value->text()));
        } else if (pair_value->name() == "UNTIL") {
          event->set_until(FromIcalendarDate(pair_value->text()));
        }
      }
    }
  }

  return event;
}

/*
ABNF-грамматика нетерминала date-time спецификации iCalendar:

date-time   = date "T" time

date        = date-year date-month date-day
date-year   = 4DIGIT
date-month  = 2DIGIT
date-day    = 2DIGIT

time        = time-hour time-minute time-second [time-utc]
time-hour   = 2DIGIT
time-minute = 2DIGIT
time-second = 2DIGIT
time-utc    = "Z"
*/

// TODO(affeeal): проверять на соответствие формату
Wt::WDateTime CalendarConverter::FromIcalendarDateTime(
    const std::string& icalendar_date_time) {
  return Wt::WDateTime::fromString(icalendar_date_time, kDateTimeFormat);
}

Wt::WDate CalendarConverter::FromIcalendarDate(
    const std::string& icalendar_date) {
  return Wt::WDate::fromString(icalendar_date, kDateFormat);
}

std::unique_ptr<ICharReader> CalendarConverter::CalendarToIcalendar(
    std::vector<CalendarSptr>&& calendars) {
  std::stringstream ss;

  for (CalendarSptr calendar : calendars) {
    Write(ss, "BEGIN", "VCALENDAR");

    // установка свойств календаря
    Write(ss, "VERSION", "2.0");
    Write(ss, "PRODID", "calendula.ru");
    Write(ss, "CALSCALE", "GREGORIAN");
    Write(ss, "METHOD", "PUBLISH");
    Write(ss, "X-WR-CALNAME:", calendar->summary());
    Write(ss, "X-CALENDULA-DESCRIPTION:", calendar->description());
    Write(ss, "X-CALENDULA-COLOR:", calendar->color());
    Write(ss, "X-CALENDULA-VISIBILITY:", calendar->visibility());

    for (std::size_t event_id : calendar->events_id()) {
      // получить event из БД по id
      EventSptr event_dummy;
      
      Write(ss, "BEGIN", "VEVENT");

      // TODO(affeeal): установить UID
      Write(ss, "SUMMARY", event_dummy->summary());
      // TODO(affeeal): установить DTSTAMP
      Write(ss, "DTSTART", FromCalendarDateTime(event_dummy->start()));
      Write(ss, "DTEND", FromCalendarDateTime(event_dummy->end()));
      Write(ss, "DESCRIPTION", event_dummy->description());
      // TODO(affeeal): установить LOCATION
      if (event_dummy->is_recurrent()) {
        Write(ss, "RRULE", FromCalendarRrule(event_dummy));
      }

      Write(ss, "END", "VEVENT");
    }

    Write(ss, "END", "VCALENDAR");
  }

  return std::make_unique<StringCharacterReader>(std::move(ss));
}

void CalendarConverter::Write(
    std::stringstream& ss,
    const Wt::WString& name,
    const Wt::WString& value) {
  ss << name.toUTF8() << ":" << value.toUTF8() << "\r\n";
}

Wt::WString CalendarConverter::FromCalendarDateTime(
    const Wt::WDateTime& date_time) {
  return date_time.toString(kDateTimeFormat);
}

Wt::WString CalendarConverter::FromCalendarRrule(const EventSptr event) {
  std::stringstream ss;

  ss << "FREQ=" << event->frequency();
  ss << ";INTERVAL=" << std::to_string(event->interval());
  ss << ";UNTIL=" << FromCalendarDate(event->until());

  return ss.str();
}

Wt::WString CalendarConverter::FromCalendarDate(const Wt::WDate& date) {
  return date.toString(kDateFormat);
}

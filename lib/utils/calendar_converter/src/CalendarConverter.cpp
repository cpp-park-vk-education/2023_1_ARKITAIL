#include "CalendarConverter.hpp"

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <Wt/WDateTime.h>
#include <Wt/WString.h>

#include "ICharacterReader.hpp"
#include "IStreamBuffer.hpp"

#include "Calendar.hpp"
#include "Event.hpp"
#include "IstreamCharacterReader.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "SessionScopeMap.hpp"

const std::string kDateTimeFormat = "yyyyMMdd'T'hhmmss'Z'";
const std::string kDateFormat = "yyyyMMdd";

std::vector<size_t> CalendarConverter::IcalendarToCalendars(
    std::unique_ptr<parsing::ICharacterReader>&& char_reader) {
  // установка связей между char_reader, lexer, parser
  parsing::IcalendarLexer lexer;
  lexer.set_character_reader(*char_reader);

  parsing::IcalendarParser parser;
  parser.set_lexer(lexer);

  // возвращаемые id календарей
  std::vector<size_t> calendars;

  // корень AST
  parsing::StreamUptr root = parser.Parse();

  // не удалось распарсить или пустой stream
  if (!root || root->components().empty()) {
    return std::vector<size_t>();
  }

  // менджеры, через которые будут сохраняться
  // разобранные календари и их события
  auto managers = SessionScopeMap::instance().get()->managers();

  // проходимся по всем распаршенным календарям
  for (parsing::ComponentUptr& component : root->components()) {
    // нас интересуют только календари
    if (component->name() != "VCALENDAR") {
      continue;
    }

    CalendarSptr calendar;
    std::vector<EventSptr> events;

    std::vector<parsing::PropertyUptr>& calendar_properties = component->properties();
    for (parsing::PropertyUptr& property : calendar_properties) {
      if (property->name() == "X-WR-CALNAME") {
        parsing::TextValue* value = dynamic_cast<parsing::TextValue*>(property->value().get());
        if (value) {
          calendar->summary = std::move(value->text());
        }
      } else if (property->name() == "X-CALENDULA-DESCRIPTION") {
        parsing::TextValue* value = dynamic_cast<parsing::TextValue*>(property->value().get());
        if (value) {
          calendar->description = std::move(value->text());
        }
      } else if (property->name() == "X-CALENDULA-COLOR") {
        parsing::TextValue* value = dynamic_cast<parsing::TextValue*>(property->value().get());
        if (value) {
          calendar->color = std::move(value->text());
        }
      } else if (property->name() == "X-CALENDULA-VISIBILITY") {
        parsing::TextValue* value = dynamic_cast<parsing::TextValue*>(property->value().get());
        if (value) {
          calendar->visibility = std::move(value->text());
        }
      }
    }

    std::vector<parsing::ComponentUptr>& calendar_components = component->components();
    for (parsing::ComponentUptr& component : calendar_components) {
      // ищем только события
      if (component->name() != "VEVENT") {
        continue;
      }

      events.push_back(FromIcalendarEvent(component));
    }

    size_t calendar_id = managers->calendar_manager()->add(calendar);
    for (EventSptr event : events) {
      event->calendar_id = calendar_id;
      managers->event_manager()->add(event);
    }

    calendars.push_back(calendar_id);
  }

  return calendars;
}

EventSptr CalendarConverter::FromIcalendarEvent(
    const parsing::ComponentUptr& icalendar_event) {
  EventSptr event;

  std::vector<parsing::PropertyUptr>& event_propeties = icalendar_event->properties();

  for (parsing::PropertyUptr& property : event_propeties) {
    if (property->name() == "SUMMARY") {
      parsing::TextValue* value = dynamic_cast<parsing::TextValue*>(property->value().get());
      if (value) {
        event->summary = value->text();
      }
    } else if (property->name() == "DESCRIPTION") {
      parsing::TextValue* value = dynamic_cast<parsing::TextValue*>(property->value().get());
      if (value) {
        event->description = value->text();
      }
    } else if (property->name() == "DTSTART") {
      parsing::TextValue* value = dynamic_cast<parsing::TextValue*>(property->value().get());
      if (value) {
        event->start = FromIcalendarDateTime(value->text());
      }
    } else if (property->name() == "DTEND") {
      parsing::TextValue* value = dynamic_cast<parsing::TextValue*>(property->value().get());
      if (value) {
        event->end = FromIcalendarDateTime(value->text());
      }
    } else if (property->name() == "RRULE") {
      parsing::CompositeValue* composite_value
        = dynamic_cast<parsing::CompositeValue*>(property->value().get());
      if (!composite_value) {
        continue;
      }

      event->is_recurrent = true;

      for (parsing::IValueUptr& value : composite_value->values()) {
        parsing::PairValue* pair_value = dynamic_cast<parsing::PairValue*>(value.get());
        if (!pair_value) {
          continue;
        }

        if (pair_value->name() == "FREQ") {
          event->frequency = pair_value->text();
        } else if (pair_value->name() == "INTERVAL") {
          // TODO(affeeal): проверка на "не число"
          event->interval = std::stoul(pair_value->text());
        } else if (pair_value->name() == "UNTIL") {
          event->until = FromIcalendarDate(pair_value->text());
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

std::unique_ptr<parsing::IStreamBuffer> CalendarConverter::CalendarsToIcalendar(
    const std::vector<size_t>& calendars) {
  std::stringstream ss;

  auto calendar_manager
    = SessionScopeMap::instance().get()->managers()->calendar_manager();
  for (size_t calendar_id : calendars) {
    CalendarSptr calendar = calendar_manager->get(calendar_id);
    
    Write(ss, "BEGIN", "VCALENDAR");

    // установка свойств календаря
    Write(ss, "VERSION", "2.0");
    Write(ss, "PRODID", "calendula.ru");
    Write(ss, "CALSCALE", "GREGORIAN");
    Write(ss, "METHOD", "PUBLISH");
    Write(ss, "X-WR-CALNAME:", calendar->summary);
    Write(ss, "X-CALENDULA-DESCRIPTION:", calendar->description);
    Write(ss, "X-CALENDULA-COLOR:", calendar->color);
    Write(ss, "X-CALENDULA-VISIBILITY:", calendar->visibility);

    std::vector<EventSptr> events = calendar_manager->getEvents(calendar_id);
    for (EventSptr event : events) {
      Write(ss, "BEGIN", "VEVENT");

      // TODO(affeeal): установить UID
      Write(ss, "SUMMARY", event->summary);
      // TODO(affeeal): установить DTSTAMP
      Write(ss, "DTSTART", FromCalendarDateTime(event->start));
      Write(ss, "DTEND", FromCalendarDateTime(event->end));
      Write(ss, "DESCRIPTION", event->description);
      // TODO(affeeal): установить LOCATION
      if (event->is_recurrent) {
        Write(ss, "RRULE", FromCalendarRrule(event));
      }

      Write(ss, "END", "VEVENT");
    }

    Write(ss, "END", "VCALENDAR");
  }

  return std::make_unique<parsing::IstreamCharacterReader>(ss.rdbuf());
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

  ss << "FREQ=" << event->frequency;
  ss << ";INTERVAL=" << std::to_string(event->interval);
  ss << ";UNTIL=" << FromCalendarDate(event->until);

  return ss.str();
}

Wt::WString CalendarConverter::FromCalendarDate(const Wt::WDate& date) {
  return date.toString(kDateFormat);
}

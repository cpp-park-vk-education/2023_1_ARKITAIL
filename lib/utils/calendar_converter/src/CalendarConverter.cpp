#include "CalendarConverter.hpp"

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <Wt/WDateTime.h>
#include <Wt/WString.h>

#include "Calendar.hpp"
#include "Event.hpp"
#include "IstreamReader.hpp"
#include "IcalendarLexer.hpp"
#include "IcalendarParser.hpp"
#include "SessionScopeMap.hpp"

namespace converter {
const std::string kDateTimeFormat = "yyyyMMdd'T'hhmmss'Z'";
const std::string kDateFormat = "yyyyMMdd";

std::vector<CalendarSptr> CalendarConverter::IcalendarToCalendars(
    std::unique_ptr<std::istream>&& source) {
  // установка связей между char_reader, lexer, parser
  reader::IstreamReader reader(std::move(source));
  
  lexer::IcalendarLexer lexer;
  lexer.set_reader(reader);

  parser::IcalendarParser parser;
  parser.set_lexer(lexer);

  // возвращаемые календари
  std::vector<CalendarSptr> calendars;

  parser::StreamUptr root = parser.Parse();

  // не удалось распарсить или пустой stream
  if (!root || root->components().empty()) {
    return calendars;
  }

  auto managers = SessionScopeMap::instance().get()->managers();

  // проходимся по всем разобранным календарям
  for (parser::ComponentUptr& component : root->components()) {
    // нас интересуют только календари
    if (component->name() != "VCALENDAR") {
      continue;
    }

    Calendar calendar;
    std::vector<EventSptr> events;

    std::vector<parser::PropertyUptr>& calendar_properties
      = component->properties();
    for (parser::PropertyUptr& property : calendar_properties) {
      if (property->name() == "X-WR-CALNAME") {
        parser::TextValue* text_value
          = dynamic_cast<parser::TextValue*>(property->value().get());
        if (text_value) {
          calendar.summary = std::move(text_value->text());
        }
      } else if (property->name() == "X-CALENDULA-DESCRIPTION") {
        parser::TextValue* text_value
          = dynamic_cast<parser::TextValue*>(property->value().get());
        if (text_value) {
          calendar.description = std::move(text_value->text());
        }
      } else if (property->name() == "X-CALENDULA-COLOR") {
        parser::TextValue* text_value
          = dynamic_cast<parser::TextValue*>(property->value().get());
        if (text_value) {
          calendar.color = std::move(text_value->text());
        }
      } else if (property->name() == "X-CALENDULA-VISIBILITY") {
        parser::TextValue* text_value
          = dynamic_cast<parser::TextValue*>(property->value().get());
        if (text_value) {
          calendar.visibility = std::move(text_value->text());
        }
      }
    }

    std::vector<parser::ComponentUptr>& calendar_components
      = component->components();
    for (parser::ComponentUptr& component : calendar_components) {
      // ищем только события
      if (component->name() != "VEVENT") {
        continue;
      }

      events.push_back(FromIcalendarEvent(component));
    }

    size_t calendar_id = managers->calendar_manager()->add(
        std::make_shared<Calendar>(calendar));
    for (EventSptr event : events) {
      event->calendar_id = calendar_id;
      managers->event_manager()->add(event);
    }

    // вновь запрашиваю текущий календарь,
    // у которого теперь установлены все поля
    calendars.push_back(managers->calendar_manager()->get(calendar_id));
  }

  return calendars;
}

EventSptr CalendarConverter::FromIcalendarEvent(
    const parser::ComponentUptr& icalendar_event) {
  Event event;

  std::vector<parser::PropertyUptr>& event_propeties
    = icalendar_event->properties();

  for (parser::PropertyUptr& property : event_propeties) {
    if (property->name() == "SUMMARY") {
      parser::TextValue* text_value
        = dynamic_cast<parser::TextValue*>(property->value().get());
      if (text_value) {
        event.summary = text_value->text();
      }
    } else if (property->name() == "DESCRIPTION") {
      parser::TextValue* text_value
        = dynamic_cast<parser::TextValue*>(property->value().get());
      if (text_value) {
        event.description = text_value->text();
      }
    } else if (property->name() == "LOCATION") {
      parser::TextValue* text_value
        = dynamic_cast<parser::TextValue*>(property->value().get());
      if (text_value) {
        event.location = text_value->text();
      }
    } else if (property->name() == "DTSTART") {
      parser::TextValue* text_value
        = dynamic_cast<parser::TextValue*>(property->value().get());
      if (text_value) {
        event.start = FromIcalendarDateTime(text_value->text());
      }
    } else if (property->name() == "DTEND") {
      parser::TextValue* text_value
        = dynamic_cast<parser::TextValue*>(property->value().get());
      if (text_value) {
        event.end = FromIcalendarDateTime(text_value->text());
      }
    } else if (property->name() == "DTSTAMP") {
      parser::TextValue* text_value
        = dynamic_cast<parser::TextValue*>(property->value().get());
      if (text_value) {
        event.stamp = FromIcalendarDateTime(text_value->text());
      }
    } else if (property->name() == "RRULE") {
      parser::CompositeValue* composite_value
        = dynamic_cast<parser::CompositeValue*>(property->value().get());

      if (!composite_value) {
        continue;
      }

      for (parser::IValueUptr& value : composite_value->values()) {
        parser::PairValue* pair_value
          = dynamic_cast<parser::PairValue*>(value.get());
        if (!pair_value) {
          continue;
        }

        if (pair_value->name() == "FREQ") {
          event.frequency = pair_value->text();
        } else if (pair_value->name() == "INTERVAL") {
          // TODO(affeeal): проверка на "не число"
          event.interval = std::stoul(pair_value->text());
        } else if (pair_value->name() == "UNTIL") {
          event.until = FromIcalendarDate(pair_value->text());
        }
      }
    }
  }

  return std::make_shared<Event>(event);
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

std::unique_ptr<std::istream> CalendarConverter::CalendarsToIcalendar(
    const std::vector<CalendarSptr>& calendars) {
  std::stringstream source;

  for (CalendarSptr calendar : calendars) {
    Write(source, "BEGIN", "VCALENDAR");

    // установка свойств календаря
    Write(source, "VERSION", "2.0");
    Write(source, "PRODID", "calendula.ru");
    Write(source, "CALSCALE", "GREGORIAN");
    Write(source, "METHOD", "PUBLISH");
    Write(source, "X-WR-CALNAME", calendar->summary);
    Write(source, "X-CALENDULA-DESCRIPTION", calendar->description);
    Write(source, "X-CALENDULA-COLOR", calendar->color);
    Write(source, "X-CALENDULA-VISIBILITY", calendar->visibility);

    auto managers = SessionScopeMap::instance().get()->managers();
    std::vector<Event> events
        = managers->calendar_manager()->getEvents(calendar->id);

    for (Event& event : events) {
      Write(source, "BEGIN", "VEVENT");

      // TODO(affeeal): установить UID
      Write(source, "SUMMARY", event.summary);
      Write(source, "DTSTAMP", FromCalendarDateTime(event.stamp));
      Write(source, "DTSTART", FromCalendarDateTime(event.start));
      Write(source, "DTEND", FromCalendarDateTime(event.end));
      Write(source, "DESCRIPTION", event.description);
      Write(source, "LOCATION", event.location);
      if (event.IsRecurrent()) {
        Write(source, "RRULE", FromCalendarRrule(event));
      }

      Write(source, "END", "VEVENT");
    }

    Write(source, "END", "VCALENDAR");
  }

  return std::make_unique<std::stringstream>(std::move(source));
}

void CalendarConverter::Write(
    std::stringstream& ss,
    const std::string& name,
    const std::string& value) {
  ss << name << ":" << value << "\r\n";
}

std::string CalendarConverter::FromCalendarDateTime(
    const Wt::WDateTime& date_time) {
  return date_time.toString(kDateTimeFormat).toUTF8();
}

std::string CalendarConverter::FromCalendarRrule(const Event& event) {
  std::stringstream source;

  source << "FREQ=" << event.frequency;
  source << ";INTERVAL=" << std::to_string(event.interval);
  source << ";UNTIL=" << FromCalendarDate(event.until);

  return source.str();
}

std::string CalendarConverter::FromCalendarDate(const Wt::WDate& date) {
  return date.toString(kDateFormat).toUTF8();
}

std::unique_ptr<std::istream> CalendarConverter::CalendarToIcalendar(
    CalendarSptr calendar) {
  return CalendarsToIcalendar(std::vector<CalendarSptr> { calendar } );
}
} // namespace converter

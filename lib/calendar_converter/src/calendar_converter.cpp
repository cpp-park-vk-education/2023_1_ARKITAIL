#include "calendar_converter.hpp"

#include <Wt/WDateTime.h>
#include <chrono>
#include <memory>
#include <iostream>
#include <vector>

#include "i_char_reader.hpp"

#include "calendar.hpp"
#include "lexer.hpp"
#include "parser.hpp"

std::vector<CalendarSptr> CalendarConverter::IcalendarToCalendar(
    std::unique_ptr<ICharReader> &&char_reader) {
  // установка связей между char_reader, lexer, parser
  char_reader_ = std::move(char_reader);

  iCalendarLexer lexer;
  lexer.set_character_reader(*char_reader_);

  iCalendarParser parser;
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

    Calendar calendar;

    std::vector<PropertyUptr>& calendar_properties = component->properties();
    for (PropertyUptr& property : calendar_properties) {
      // ищем только свойство X-WR-CALNAME - название календаря
      if (property->name() != "X-WR-CALNAME") {
        continue;
      }

      // значение свойства должно быть TextValue
      TextValue* value = dynamic_cast<TextValue*>(property->value().get());
      if (value) {
        calendar.title = std::move(value->text());
      }
      break;
    }

    std::vector<ComponentUptr>& calendar_components = component->components();
    for (ComponentUptr& component : calendar_components) {
      // ищем только события
      if (component->name() != "VEVENT") {
        continue;
      }

      calendar.events.push_back(FromIcalendarEvent(component));
    }

    calendars.push_back(std::make_shared<Calendar>(calendar));
  }

  return calendars;
}

std::shared_ptr<Event> CalendarConverter::FromIcalendarEvent(
    const ComponentUptr& icalendar_event) {
  Event event;

  std::vector<PropertyUptr>& event_propeties = icalendar_event->properties();

  for (PropertyUptr& property : event_propeties) {
    if (property->name() == "SUMMARY") {
      TextValue* value = dynamic_cast<TextValue*>(property->value().get());
      if (value) {
        event.summary = value->text();
      }
    } else if (property->name() == "DESCRIPTION") {
      TextValue* value = dynamic_cast<TextValue*>(property->value().get());
      if (value) {
        event.description = value->text();
      }
    } else if (property->name() == "DTSTART") {
      TextValue* value = dynamic_cast<TextValue*>(property->value().get());
      if (value) {
        event.start = FromIcalendarDateTime(value->text());
      }
    } else if (property->name() == "DTEND") {
      TextValue* value = dynamic_cast<TextValue*>(property->value().get());
      if (value) {
        event.end = FromIcalendarDateTime(value->text());
      }
    }
    // TODO(affeeal): повторяемость
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
  return Wt::WDateTime::fromString(icalendar_date_time, "yyyyMMdd'T'hhmmss'Z'");
}

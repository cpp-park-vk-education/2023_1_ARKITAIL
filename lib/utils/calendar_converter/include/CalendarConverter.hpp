#pragma once

#include <memory>
#include <string>
#include <vector>

#include <Wt/WDateTime.h>
#include <Wt/WDate.h>

#include "IParser.hpp"
#include "Event.hpp"
#include "Calendar.hpp"

namespace converter {
class CalendarConverter {
 public:
  static std::vector<CalendarSptr> IcalendarToCalendars(
      std::unique_ptr<std::istream>&& source);

  static std::unique_ptr<std::istream> CalendarsToIcalendar(
      const std::vector<CalendarSptr>& calendars);
  static std::unique_ptr<std::istream> CalendarToIcalendar(
      CalendarSptr calendar);

 private:
  static EventSptr FromIcalendarEvent(const parser::ComponentUptr& icalendar_event);
  static Wt::WDateTime FromIcalendarDateTime(const std::string& icalendar_date_time);
  static Wt::WDate FromIcalendarDate(const std::string& icalendar_date);
  
  static void Write(std::stringstream& source, const std::string& name,
    const std::string& value);

  static std::string FromCalendarDateTime(const Wt::WDateTime& date_time);
  static std::string FromCalendarRrule(const Event& event);
  static std::string FromCalendarDate(const Wt::WDate& date);
};
} // namespace converter

#pragma once

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <Wt/WDateTime.h>
#include <Wt/WDate.h>
#include <Wt/WString.h>

#include "Event.hpp"
#include "ICalendarConverter.hpp"
#include "ICharacterReader.hpp"
#include "Calendar.hpp"
#include "Parser.hpp"

class CalendarConverter : ICalendarConverter {
 public:
   std::vector<CalendarSptr> IcalendarToCalendar(
       std::unique_ptr<ICharReader>&& char_reader) override;

  std::unique_ptr<ICharReader> CalendarToIcalendar(
      std::vector<CalendarSptr>&& calendars) override;
 private:
  EventSptr FromIcalendarEvent(const ComponentUptr& icalendar_event);
  Wt::WDateTime FromIcalendarDateTime(const std::string& icalendar_date_time);
  Wt::WDate FromIcalendarDate(const std::string& icalendar_date);
  
  void Write(
    std::stringstream& ss,
    const Wt::WString& name,
    const Wt::WString& value);

  Wt::WString FromCalendarDateTime(const Wt::WDateTime& date_time);
  Wt::WString FromCalendarRrule(const EventSptr event);
  Wt::WString FromCalendarDate(const Wt::WDate& date);
};

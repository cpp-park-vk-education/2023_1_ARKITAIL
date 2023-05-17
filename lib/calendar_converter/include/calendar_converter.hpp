#pragma once

#include <memory>
#include <vector>

#include <Wt/WDateTime.h>

#include "i_calendar_converter.hpp"
#include "i_char_reader.hpp"
#include "calendar.hpp"
#include "parser.hpp"

class CalendarConverter : ICalendarConverter {
 public:
   std::vector<CalendarSptr> IcalendarToCalendar(
       std::unique_ptr<ICharReader> &&char_reader) override;
 private:
  EventSptr FromIcalendarEvent(const ComponentUptr& icalendar_event);
  Wt::WDateTime FromIcalendarDateTime(const std::string& icalendar_date_time);

  std::unique_ptr<ICharReader> char_reader_;
};

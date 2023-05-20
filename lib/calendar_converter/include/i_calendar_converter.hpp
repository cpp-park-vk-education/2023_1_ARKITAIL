#pragma once

#include <memory>
#include <vector>

#include "calendar.hpp"
#include "i_char_reader.hpp"

class ICalendarConverter {
 public:
  // iCalendar stream может содержать несколько календарей,
  // поэтому возвращаем вектор
  virtual std::vector<CalendarSptr> IcalendarToCalendar(
      std::unique_ptr<ICharReader>&& char_reader) = 0;

  virtual std::unique_ptr<ICharReader> CalendarToIcalendar(
      std::vector<CalendarSptr>&& calendars) = 0;

  virtual ~ICalendarConverter() = default;
};

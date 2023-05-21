#pragma once

#include <memory>
#include <vector>

#include "ICharacterReader.hpp"
#include "IStreamBuffer.hpp"

#include "Calendar.hpp"

class ICalendarConverter {
 public:
  virtual std::vector<CalendarSptr> IcalendarToCalendars(
      std::unique_ptr<ICharacterReader>&& reader) = 0;

  virtual std::unique_ptr<IStreamBuffer> CalendarsToIcalendar(
      const std::vector<CalendarSptr>& calendars) = 0;

  virtual ~ICalendarConverter() = default;
};

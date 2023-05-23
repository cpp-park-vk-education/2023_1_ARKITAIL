#pragma once

#include "Calendar.hpp"
#include "CalendarView.hpp"

namespace dialog {
class EditCalendarView : public CalendarView {
 public:
  EditCalendarView(CalendarSptr calendar);
};
} // namespace dialog

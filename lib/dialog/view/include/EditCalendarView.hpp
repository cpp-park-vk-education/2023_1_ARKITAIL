#pragma once

#include "Calendar.hpp"
#include "CalendarView.hpp"

namespace dialog {
class EditCalendarView : public CalendarView {
 public:
  EditCalendarView(CalendarSptr calendar);

  Wt::Signal<CalendarSptr>& calendar_updated();
 private:
  void InitializeButton() override;

  void HandleInput() override;

  Wt::Signal<CalendarSptr> calendar_updated_;
};
} // namespace dialog

#pragma once

#include "Calendar.hpp"
#include "CalendarView.hpp"

namespace dialog {
class CreateCalendarView : public CalendarView {
 public:
  CreateCalendarView();

  Wt::Signal<CalendarSptr>& calendar_created();
 private:
  void InitializeButton() override;

  void HandleInput() override;

  Wt::Signal<CalendarSptr> calendar_created_;
};
} // namespace dialog

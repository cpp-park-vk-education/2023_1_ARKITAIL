#pragma once

#include "CalendarModel.hpp"

namespace dialog {
class EditCalendarModel : public CalendarModel {
 public:
  explicit EditCalendarModel(CalendarSptr calendar);

  void UpdateCalendar() override;
 private:
  void SetValues() override;
};
} // namespace dialog

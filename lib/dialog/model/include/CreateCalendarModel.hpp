#pragma once

#include "CalendarModel.hpp"

namespace dialog {
class CreateCalendarModel : public CalendarModel {
 public:
  CreateCalendarModel();

  void UpdateCalendar() override;
 private:
  void SetValues() override;
};
} // namespace dialog

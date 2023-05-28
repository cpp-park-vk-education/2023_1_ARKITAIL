#pragma once

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>

#include "Calendar.hpp"

namespace dialog {
class CalendarModel : public Wt::WFormModel {
 public:
  static const Wt::WFormModel::Field kSummary;
  static const Wt::WFormModel::Field kDescription;
  static const Wt::WFormModel::Field kVisibility;
  static const Wt::WFormModel::Field kColor;

  explicit CalendarModel(CalendarSptr calendar = nullptr);

  void UpdateCalendar();

  CalendarSptr calendar() const;

  void set_calendar(CalendarSptr calendar);
 private:
  void AddFields();
  void SetValidators();
  void SetValues();

  std::shared_ptr<Wt::WValidator> CreateTitleValidator();

  CalendarSptr calendar_;
};
} // namespace dialog

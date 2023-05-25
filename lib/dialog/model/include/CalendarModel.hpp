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

  virtual void UpdateCalendar();

  CalendarSptr calendar() const;

  void set_calendar(CalendarSptr calendar);
 protected:
  explicit CalendarModel(CalendarSptr calendar);

  void AddFields();
  void SetValidators();
  virtual void SetValues();

  std::shared_ptr<Wt::WValidator> CreateTitleValidator();

  CalendarSptr calendar_;
};
} // namespace dialog

#pragma once

#include <memory>

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

  // заполение полей calendar_ актуальными данными формы; переопределяется
  // классами EditCalendarSettingsModel и CreateCalendarSettingsModel
  virtual void UpdateCalendar();

  CalendarSptr calendar() const;

  void set_calendar(CalendarSptr calendar);
 protected:
  // экземпляры создаются наследниками
  CalendarModel() = delete;
  CalendarModel(CalendarSptr calendar);

  // привязка полей к форме
  void AddFields();
  // установка валидаторов полям формы
  void SetValidators();
  // установка начальных значений полей формы; переопределяется классами
  // EditCalendarSettingsModel и CreateCalendarSettingsModel
  virtual void SetValues();

  std::shared_ptr<Wt::WValidator> CreateTitleValidator();

  CalendarSptr calendar_;
};
} // namespace dialog

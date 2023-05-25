#include "CalendarModel.hpp"

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>
#include <Wt/WLengthValidator.h>

#include "Calendar.hpp"

namespace dialog {
const Wt::WFormModel::Field CalendarModel::kSummary = "summary";
const Wt::WFormModel::Field CalendarModel::kDescription = "description";
const Wt::WFormModel::Field CalendarModel::kVisibility = "visibility";
const Wt::WFormModel::Field CalendarModel::kColor = "color";

void CalendarModel::UpdateCalendar() {
}

CalendarSptr CalendarModel::calendar() const {
  return calendar_;
}

void CalendarModel::set_calendar(CalendarSptr calendar) {
  calendar_ = calendar;
}

// по умолчанию calendar = nullptr
CalendarModel::CalendarModel(CalendarSptr calendar)
    : Wt::WFormModel(),
      calendar_(calendar) {
  AddFields();
  SetValidators();
  SetValues();
}

void CalendarModel::AddFields() {
  addField(kSummary);
  addField(kDescription);
  addField(kVisibility);
  addField(kColor);
}

void CalendarModel::SetValidators() {
  setValidator(kSummary, CreateTitleValidator());
  validator(kSummary)->setMandatory(true);
}

void CalendarModel::SetValues() {
}

std::shared_ptr<Wt::WValidator> CalendarModel::CreateTitleValidator() {
  auto validator = std::make_shared<Wt::WLengthValidator>();

  validator->setMinimumLength(1);
  validator->setMaximumLength(50);

  return validator;
}
} // namespace dialog

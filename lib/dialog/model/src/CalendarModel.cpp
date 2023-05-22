#include "CalendarModel.hpp"

#include <memory>

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

// по умолчанию calendar = nullptr
CalendarModel::CalendarModel(CalendarSptr calendar)
    : Wt::WFormModel(),
      calendar_(calendar) {
  AddFields();
  SetValidators();
  SetValues();
}

CalendarSptr CalendarModel::calendar() const {
  return calendar_;
}

void CalendarModel::set_calendar(CalendarSptr calendar) {
  calendar_ = calendar;
}

void CalendarModel::AddFields() {
  addField(kSummary);
  addField(kDescription);
  addField(kVisibility);
  addField(kColor);
}

void CalendarModel::SetValidators() {
  setValidator(kSummary, CreateTitleValidator());
}

void CalendarModel::SetValues() {
}

std::shared_ptr<Wt::WValidator> CalendarModel::CreateTitleValidator() {
  auto validator = std::make_shared<Wt::WLengthValidator>();

  validator->setMandatory(true);
  validator->setMinimumLength(1);
  validator->setMaximumLength(50);

  return validator;
}
} // namespace dialog

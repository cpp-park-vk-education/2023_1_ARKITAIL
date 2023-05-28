#include "CalendarModel.hpp"

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>
#include <Wt/WLengthValidator.h>
#include <Wt/WLogger.h>

#include "Calendar.hpp"

namespace dialog {
const Wt::WFormModel::Field CalendarModel::kSummary = "summary";
const Wt::WFormModel::Field CalendarModel::kDescription = "description";
const Wt::WFormModel::Field CalendarModel::kVisibility = "visibility";
const Wt::WFormModel::Field CalendarModel::kColor = "color";

// по умолчанию calendar = nullptr
CalendarModel::CalendarModel(CalendarSptr calendar)
    : Wt::WFormModel(),
      calendar_(calendar) {
  AddFields();
  SetValidators();
  SetValues();
}

void CalendarModel::UpdateCalendar() {
  if (!calendar_) {
    calendar_ = std::make_shared<Calendar>();
  }

  calendar_->summary = Wt::asString(value(kSummary)).toUTF8();
  calendar_->description = Wt::asString(value(kDescription)).toUTF8();
  calendar_->visibility = Wt::asString(value(kVisibility)).toUTF8();
  calendar_->color = Wt::asString(value(kColor)).toUTF8();
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
  validator(kSummary)->setMandatory(true);
}

void CalendarModel::SetValues() {
  if (calendar_) {
    setValue(kSummary, calendar_->summary);
    setValue(kDescription, calendar_->description);
    setValue(kVisibility, calendar_->visibility);
    setValue(kColor, calendar_->color);
  } else {
    // Установить значения по умолчанию
    setValue(kColor, "#f4d03f");
  }
}

std::shared_ptr<Wt::WValidator> CalendarModel::CreateTitleValidator() {
  auto validator = std::make_shared<Wt::WLengthValidator>();

  validator->setInvalidBlankText("Пожалуйста, укажите название");
  validator->setMinimumLength(1);
  validator->setMaximumLength(50);

  return validator;
}
} // namespace dialog

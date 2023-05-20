#include "CalendarSettingsModel.hpp"

#include <memory>

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>
#include <Wt/WLengthValidator.h>

#include "Calendar.hpp"

const Wt::WFormModel::Field CalendarSettingsModel::kSummary = "summary";
const Wt::WFormModel::Field CalendarSettingsModel::kDescription = "description";
const Wt::WFormModel::Field CalendarSettingsModel::kVisibility = "visibility";
const Wt::WFormModel::Field CalendarSettingsModel::kColor = "color";

// по умолчаню caledar = nullptr
CalendarSettingsModel::CalendarSettingsModel(
    CalendarSptr calendar) : Wt::WFormModel() {
  addField(kSummary);
  addField(kDescription);
  addField(kVisibility);
  addField(kColor);

  setValidator(kSummary, CreateTitleValidator());

  if (calendar) {
    setValue(kSummary, calendar->summary());
    setValue(kDescription, calendar->description());
    setValue(kVisibility, calendar->visibility());
    setValue(kColor, calendar->color());
  }
}

std::shared_ptr<Wt::WValidator> CalendarSettingsModel::CreateTitleValidator() {
  auto validator = std::make_shared<Wt::WLengthValidator>();

  validator->setMandatory(true);
  validator->setMinimumLength(1);
  validator->setMaximumLength(50);

  return validator;
}

std::shared_ptr<Calendar> CalendarSettingsModel::GetData() const {
  auto calendar = std::make_shared<Calendar>();

  calendar->set_summary(Wt::asString(value(kSummary)));
  calendar->set_description(Wt::asString(value(kDescription)));
  calendar->set_visibility(Wt::asString(value(kVisibility)));
  calendar->set_color(Wt::asString(value(kColor)));

  return calendar;
}

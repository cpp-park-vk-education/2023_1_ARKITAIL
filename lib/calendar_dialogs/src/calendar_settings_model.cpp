#include "calendar_settings_model.hpp"

#include <Wt/WAny.h>
#include <memory>

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>
#include <Wt/WLengthValidator.h>

const Wt::WFormModel::Field CalendarSettingsModel::kTitleField = "title";
const Wt::WFormModel::Field CalendarSettingsModel::kDescriptionField = "description";
const Wt::WFormModel::Field CalendarSettingsModel::kVisibilityField = "visibility";
const Wt::WFormModel::Field CalendarSettingsModel::kColorField = "color";

// по умолчаню caledar = nullptr
CalendarSettingsModel::CalendarSettingsModel(
    std::shared_ptr<Calendar> calendar) : Wt::WFormModel() {
  addField(kTitleField);
  addField(kDescriptionField);
  addField(kVisibilityField);
  addField(kColorField);

  setValidator(kTitleField, CreateTitleValidator());

  if (calendar) {
    setValue(kTitleField, calendar->summary);
    setValue(kDescriptionField, calendar->description);
    setValue(kVisibilityField, calendar->visibility);
    setValue(kColorField, calendar->color);
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

  calendar->summary = Wt::asString(value(kTitleField));
  calendar->description = Wt::asString(value(kDescriptionField));
  calendar->visibility = Wt::asString(value(kVisibilityField));
  calendar->color = Wt::asString(value(kColorField));

  return calendar;
}

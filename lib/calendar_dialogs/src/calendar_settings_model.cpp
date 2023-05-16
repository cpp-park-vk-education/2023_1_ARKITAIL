#include "calendar_settings_model.hpp"

#include <memory>

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>
#include <Wt/WLengthValidator.h>

const Wt::WFormModel::Field CalendarSettingsModel::kTitleField = "title";
const Wt::WFormModel::Field CalendarSettingsModel::kDescriptionField = "description";
const Wt::WFormModel::Field CalendarSettingsModel::kVisibilityField = "visibility";
const Wt::WFormModel::Field CalendarSettingsModel::kColorField = "color";

CalendarSettingsModel::CalendarSettingsModel() : Wt::WFormModel() {
  addField(kTitleField);
  addField(kDescriptionField);
  addField(kVisibilityField);
  addField(kColorField);

  setValidator(kTitleField, CreateTitleValidator());

  setValue(kColorField, "#FCBF21");
}

std::shared_ptr<Wt::WValidator> CalendarSettingsModel::CreateTitleValidator() {
  auto validator = std::make_shared<Wt::WLengthValidator>();

  validator->setMandatory(true);
  validator->setMinimumLength(1);
  validator->setMaximumLength(50);

  return validator;
}

std::unique_ptr<Calendar> CalendarSettingsModel::GetData() const {
  // ИСПРАВИТЬ
  return nullptr;
}

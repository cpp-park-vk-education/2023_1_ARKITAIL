#pragma once

#include <memory>

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>

#include "calendar.hpp"

class CalendarSettingsModel : public Wt::WFormModel {
 public:
  static const Wt::WFormModel::Field kTitleField;
  static const Wt::WFormModel::Field kDescriptionField;
  static const Wt::WFormModel::Field kVisibilityField;
  static const Wt::WFormModel::Field kColorField;

  CalendarSettingsModel(std::unique_ptr<Calendar>&& calendar = nullptr);

  std::shared_ptr<Calendar> GetData() const;

 private:
  std::shared_ptr<Wt::WValidator> CreateTitleValidator();
  std::shared_ptr<Wt::WValidator> CreateDescriptionValidator();
};

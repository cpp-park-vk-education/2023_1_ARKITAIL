#pragma once

#include <memory>

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>

#include "calendar.hpp"

class CalendarSettingsFM : public Wt::WFormModel {
 public:
  static const Wt::WFormModel::Field kTitleField;
  static const Wt::WFormModel::Field kDescriptionField;
  static const Wt::WFormModel::Field kVisibilityField;
  static const Wt::WFormModel::Field kColorField;

  CalendarSettingsFM();

  void SetData(std::unique_ptr<Calendar> calendar);
  std::unique_ptr<Calendar> GetData();

 private:
  std::shared_ptr<Wt::WValidator> CreateTitleValidator();
  std::shared_ptr<Wt::WValidator> CreateDescriptionValidator();
};

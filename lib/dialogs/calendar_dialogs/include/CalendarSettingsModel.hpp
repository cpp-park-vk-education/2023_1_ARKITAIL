#pragma once

#include <memory>

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>

#include "Calendar.hpp"

class CalendarSettingsModel : public Wt::WFormModel {
 public:
  static const Wt::WFormModel::Field kSummary;
  static const Wt::WFormModel::Field kDescription;
  static const Wt::WFormModel::Field kVisibility;
  static const Wt::WFormModel::Field kColor;

  CalendarSettingsModel(CalendarSptr calendar = nullptr);

  std::shared_ptr<Calendar> GetData() const;
 private:
  std::shared_ptr<Wt::WValidator> CreateTitleValidator();
};

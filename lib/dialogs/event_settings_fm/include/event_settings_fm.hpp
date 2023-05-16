#pragma once

#include <memory>

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>

#include "event.hpp"

class EventSettingsFM : public Wt::WFormModel {
 public:
  static const Wt::WFormModel::Field kTitleField;
  static const Wt::WFormModel::Field kDescriptionField;
  static const Wt::WFormModel::Field kCalendarField;

  static const Wt::WFormModel::Field kBeginTimeField;
  static const Wt::WFormModel::Field kBeginDateField;
  static const Wt::WFormModel::Field kEndTimeField;
  static const Wt::WFormModel::Field kEndDateField;
  static const Wt::WFormModel::Field kAllDayField;

  static const Wt::WFormModel::Field kRepeatField;
  static const Wt::WFormModel::Field kUntilField;
  static const Wt::WFormModel::Field kIntervalField;

  EventSettingsFM();

  void SetData(std::unique_ptr<Event> event);
  std::unique_ptr<Event> GetData();

 private:
  std::shared_ptr<Wt::WValidator> CreateTitleValidator();
  std::shared_ptr<Wt::WValidator> CreateDescriptionValidator();
  std::shared_ptr<Wt::WValidator> CreateDateValidator();
  std::shared_ptr<Wt::WValidator> CreateTimeValidator();
};

enum class Repeat {
  kDay = 0,
  kWeek,
  kMonth,
  kYear,
};

#pragma once

#include <memory>

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>

#include "Event.hpp"

namespace dialog {
class EventModel : public Wt::WFormModel {
 public:
  static const Wt::WFormModel::Field kSummary;
  static const Wt::WFormModel::Field kDescription;
  static const Wt::WFormModel::Field kCalendars;

  static const Wt::WFormModel::Field kStartDate;
  static const Wt::WFormModel::Field kStartTime;
  static const Wt::WFormModel::Field kEndDate;
  static const Wt::WFormModel::Field kEndTime;

  static const Wt::WFormModel::Field kIsRecurrent;
  static const Wt::WFormModel::Field kFrequency;
  static const Wt::WFormModel::Field kInterval;
  static const Wt::WFormModel::Field kUntil;
  
  virtual void UpdateEvent();

  EventSptr event() const;

  void set_event(EventSptr event);
 protected:
  explicit EventModel(EventSptr event);

  void AddFields();
  void SetValidators();
  virtual void SetValues();
  
  std::shared_ptr<Wt::WValidator> CreateTitleValidator();
  std::shared_ptr<Wt::WValidator> CreateDateValidator();
  std::shared_ptr<Wt::WValidator> CreateTimeValidator();
  std::shared_ptr<Wt::WValidator> CreateIntValidator();

  EventSptr event_;
};
} // namespace dialog

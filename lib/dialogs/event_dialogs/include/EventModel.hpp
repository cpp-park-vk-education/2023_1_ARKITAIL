#pragma once

#include <memory>

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>

#include "Event.hpp"

class EventModel : public Wt::WFormModel {
 public:
  static const Wt::WFormModel::Field kSummary;
  static const Wt::WFormModel::Field kDescription;
  static const Wt::WFormModel::Field kCalendars;

  static const Wt::WFormModel::Field kStartDate;
  static const Wt::WFormModel::Field kStartTime;
  static const Wt::WFormModel::Field kEndDate;
  static const Wt::WFormModel::Field kEndTime;
  static const Wt::WFormModel::Field kIsAllDay;

  static const Wt::WFormModel::Field kIsRecurrent;
  static const Wt::WFormModel::Field kFrequency;
  static const Wt::WFormModel::Field kInterval;
  static const Wt::WFormModel::Field kUntil;

  EventModel(std::shared_ptr<Event> event = nullptr);

  std::shared_ptr<Event> GetData() const;
 private:
  std::shared_ptr<Wt::WValidator> CreateTitleValidator();
  std::shared_ptr<Wt::WValidator> CreateDateValidator();
  std::shared_ptr<Wt::WValidator> CreateTimeValidator();
  std::shared_ptr<Wt::WValidator> CreateIntValidator();

};

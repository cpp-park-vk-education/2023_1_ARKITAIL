#pragma once

#include <memory>

#include <Wt/WFormModel.h>
#include <Wt/WValidator.h>

#include "event.hpp"

class EventModel : public Wt::WFormModel {
 public:
  static const Wt::WFormModel::Field kTitle;
  static const Wt::WFormModel::Field kDescription;
  static const Wt::WFormModel::Field kCalendars;
  static const Wt::WFormModel::Field kBeginDate;
  static const Wt::WFormModel::Field kBeginTime;
  static const Wt::WFormModel::Field kEndDate;
  static const Wt::WFormModel::Field kEndTime;
  static const Wt::WFormModel::Field kRepeat;
  static const Wt::WFormModel::Field kUntil;

  EventModel(std::shared_ptr<Event> event = nullptr);

  std::shared_ptr<Event> GetData() const;

 private:
  std::shared_ptr<Wt::WValidator> CreateTitleValidator();
  std::shared_ptr<Wt::WValidator> CreateDateValidator();
  std::shared_ptr<Wt::WValidator> CreateTimeValidator();
};

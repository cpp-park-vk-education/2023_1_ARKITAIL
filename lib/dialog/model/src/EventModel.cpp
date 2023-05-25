#include "EventModel.hpp"

#include <memory>

#include <Wt/WDateTime.h>
#include <Wt/WDateValidator.h>
#include <Wt/WFormModel.h>
#include <Wt/WIntValidator.h>
#include <Wt/WLengthValidator.h>
#include <Wt/WString.h>
#include <Wt/WTime.h>
#include <Wt/WTimeValidator.h>
#include <Wt/WValidator.h>

#include "Event.hpp"

namespace dialog {
const Wt::WFormModel::Field EventModel::kSummary = "summary";
const Wt::WFormModel::Field EventModel::kDescription= "description";
const Wt::WFormModel::Field EventModel::kCalendars = "calendars";

const Wt::WFormModel::Field EventModel::kStartDate = "start-date";
const Wt::WFormModel::Field EventModel::kStartTime = "start-time";
const Wt::WFormModel::Field EventModel::kEndDate = "end-date";
const Wt::WFormModel::Field EventModel::kEndTime = "end-time";

const Wt::WFormModel::Field EventModel::kIsRecurrent = "is-recurrent";
const Wt::WFormModel::Field EventModel::kFrequency = "frequency";
const Wt::WFormModel::Field EventModel::kInterval = "interval";
const Wt::WFormModel::Field EventModel::kUntil = "until";

void EventModel::UpdateEvent() {
}

EventSptr EventModel::event() const {
  return event_;
}

void EventModel::set_event(EventSptr event) {
  event_ = event;
}

EventModel::EventModel(EventSptr event)
    : Wt::WFormModel(),
      event_(event) {
  AddFields();
  SetValidators();
  SetValues();
}

void EventModel::AddFields() {
  addField(kSummary);
  addField(kDescription);
  addField(kCalendars);

  addField(kStartDate);
  addField(kStartTime);
  addField(kEndDate);
  addField(kEndTime);

  addField(kIsRecurrent);
  addField(kFrequency);
  addField(kInterval);
  addField(kUntil);
}

void EventModel::SetValidators() {
  setValidator(kSummary, CreateTitleValidator());

  setValidator(kStartDate, CreateDateValidator());
  validator(kStartDate)->setMandatory(true);

  setValidator(kStartTime, CreateTimeValidator());
  validator(kStartTime)->setMandatory(true);

  setValidator(kEndDate, CreateDateValidator());
  validator(kEndDate)->setMandatory(true);

  setValidator(kEndTime, CreateTimeValidator());
  validator(kEndTime)->setMandatory(true);

  setValidator(kInterval, CreateIntValidator());
  setValidator(kUntil, CreateDateValidator());
}

void EventModel::SetValues() {
}


std::shared_ptr<Wt::WValidator> EventModel::CreateTitleValidator() {
  auto validator = std::make_shared<Wt::WLengthValidator>();

  validator->setInvalidBlankText(
      "Пожалуйста, укажите название");
  validator->setMandatory(true);
  validator->setMinimumLength(1);

  return validator;
}

std::shared_ptr<Wt::WValidator> EventModel::CreateDateValidator() {
  auto validator = std::make_shared<Wt::WDateValidator>();

  validator->setFormat("dd.MM.yyyy");
  validator->setInvalidNotADateText(
      "Пожалуйста, укажите дату в формате ДД.ММ.ГГГГ");
  validator->setInvalidBlankText(
      "Пожалуйста, укажите дату");

  return validator;
}

std::shared_ptr<Wt::WValidator> EventModel::CreateTimeValidator() {
  auto validator = std::make_shared<Wt::WTimeValidator>();

  validator->setFormat("hh:mm");
  validator->setInvalidNotATimeText(
      "Пожалуйста, укажите время в формате ЧЧ:ММ");
  validator->setInvalidBlankText(
      "Пожалуйста, укажите время");

  return validator;
}

std::shared_ptr<Wt::WValidator> EventModel::CreateIntValidator() {
  auto validator = std::make_shared<Wt::WIntValidator>();

  validator->setBottom(1);
  validator->setIgnoreTrailingSpaces(true);
  validator->setInvalidBlankText(
      "Пожалуйста, укажите интервал");
  validator->setInvalidNotANumberText(
      "Пожалуйста, укажите число");

  return validator;
}
} // namespace dialog

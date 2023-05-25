#include "EventModel.hpp"

#include <Wt/WAny.h>
#include <Wt/WDate.h>
#include <memory>

#include <Wt/WDateTime.h>
#include <Wt/WDateValidator.h>
#include <Wt/WFormModel.h>
#include <Wt/WIntValidator.h>
#include <Wt/WLengthValidator.h>
#include <Wt/WLogger.h>
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

const std::string kDateFormat = "dd.MM.yyyy";
const std::string kTimeFormat = "hh:mm";
  
// по умолчанию event = nullptr
EventModel::EventModel(EventSptr event)
    : Wt::WFormModel(),
      event_(event) {
  AddFields();
  SetValidators();
  SetValues();
}

void EventModel::UpdateEvent() {
  if (!event_) {
    event_ = std::make_shared<Event>();
  }

  event_->summary = Wt::asString(value(kSummary)).toUTF8();
  event_->description = Wt::asString(value(kDescription)).toUTF8();
  // TODO(affeeal): разобраться с event->calendars

  event_->start = Wt::WDateTime(
      Wt::WDate::fromString(Wt::asString(value(kStartDate)), kDateFormat),
      Wt::WTime::fromString(Wt::asString(value(kStartTime)), kStartTime));
  event_->end = Wt::WDateTime(
      Wt::WDate::fromString(Wt::asString(value(kEndDate)), kDateFormat),
      Wt::WTime::fromString(Wt::asString(value(kEndTime)), kStartTime));

  // исправить костыль
  event_->is_recurrent = (Wt::asString(value(kIsRecurrent)).toUTF8() == "true");
  event_->frequency = Wt::asString(value(kFrequency)).toUTF8();
  event_->interval = Wt::asNumber(value(kInterval));
  event_->until = Wt::WDate::fromString(
      Wt::asString(value(kUntil)), kDateFormat);
}

EventSptr EventModel::event() const {
  return event_;
}

void EventModel::set_event(EventSptr event) {
  event_ = event;
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
  // TODO(affeeal): разобраться с event->calendars
  if (event_) {
    setValue(kSummary, event_->summary);
    setValue(kDescription, event_->description);

    setValue(kStartDate, event_->start.date());
    setValue(kStartTime, event_->start.time());
    setValue(kEndDate, event_->end.date());
    setValue(kEndTime, event_->end.time());

    setValue(kIsRecurrent, event_->is_recurrent);
    setValue(kFrequency, event_->frequency);
    setValue(kInterval, event_->interval);
    setValue(kUntil, event_->until);
  } else {
    setValue(kStartDate, Wt::WDate::currentServerDate());
    setValue(kStartTime, Wt::WTime::currentServerTime());
    setValue(kEndDate, Wt::WDate::currentServerDate());
    setValue(kEndTime, Wt::WTime::currentServerTime().addSecs(3600));
    setValue(kIsRecurrent, true);
    setValue(kInterval, 1);
  }
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

  validator->setFormat(kDateFormat);
  validator->setInvalidNotADateText(
      "Пожалуйста, укажите дату в формате ДД.ММ.ГГГГ");
  validator->setInvalidBlankText(
      "Пожалуйста, укажите дату");

  return validator;
}

std::shared_ptr<Wt::WValidator> EventModel::CreateTimeValidator() {
  auto validator = std::make_shared<Wt::WTimeValidator>();

  validator->setFormat(kTimeFormat);
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

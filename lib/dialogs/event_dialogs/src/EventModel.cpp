#include "EventModel.hpp"

#include <memory>

#include <Wt/cpp17/any.hpp>
#include <Wt/WAny.h>
#include <Wt/WDateTime.h>
#include <Wt/WDateValidator.h>
#include <Wt/WFormModel.h>
#include <Wt/WIntValidator.h>
#include <Wt/WLengthValidator.h>
#include <Wt/WString.h>
#include <Wt/WTime.h>
#include <Wt/WTimeValidator.h>
#include <Wt/WValidator.h>

const Wt::WFormModel::Field EventModel::kSummary = "summary";
const Wt::WFormModel::Field EventModel::kDescription= "description";
const Wt::WFormModel::Field EventModel::kCalendars = "calendars";

const Wt::WFormModel::Field EventModel::kStartDate = "start-date";
const Wt::WFormModel::Field EventModel::kStartTime = "start-time";
const Wt::WFormModel::Field EventModel::kEndDate = "end-date";
const Wt::WFormModel::Field EventModel::kEndTime = "end-time";
const Wt::WFormModel::Field EventModel::kIsAllDay = "is-all-day";

const Wt::WFormModel::Field EventModel::kIsRecurrent = "is-recurrent";
const Wt::WFormModel::Field EventModel::kFrequency = "frequency";
const Wt::WFormModel::Field EventModel::kInterval = "interval";
const Wt::WFormModel::Field EventModel::kUntil = "until";

// по умолчаню event = nullptr
EventModel::EventModel(
    std::shared_ptr<Event> event) : Wt::WFormModel() {
  addField(kSummary);
  addField(kDescription);
  addField(kCalendars);

  addField(kStartDate);
  addField(kStartTime);
  addField(kEndDate);
  addField(kEndTime);
  addField(kIsAllDay);

  addField(kIsRecurrent);
  addField(kFrequency);
  addField(kInterval);
  addField(kUntil);

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

  if (event) {
    setValue(kSummary, event->summary());
    setValue(kDescription, event->description());
    // setValue(kCalendars, event->calendar());

    setValue(kStartDate, event->start().date());
    setValue(kStartTime, event->start().time());
    setValue(kEndDate, event->end().date());
    setValue(kEndTime, event->end().time());
    setValue(kIsAllDay, event->is_all_day());

    setValue(kIsRecurrent, event->is_recurrent());
    setValue(kFrequency, event->frequency());
    setValue(kInterval, event->interval());
    setValue(kUntil, event->until());
  } else {
    // значения при создании события
    // календари...

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

// Так вежливо, как в валидаторах выше, я никогда не общался...

std::shared_ptr<Event> EventModel::GetData() const {
  auto event = std::make_shared<Event>();

  event->set_summary(Wt::asString(value(kSummary)));
  event->set_description(Wt::asString(value(kDescription)));
  // event->set_calendar(Wt::asString(value(kCalendars)));

  event->set_start(Wt::WDateTime(
      Wt::cpp17::any_cast<Wt::WDate>(value(kStartDate)),
      Wt::cpp17::any_cast<Wt::WTime>(value(kStartTime))));
  event->set_end(Wt::WDateTime(
      Wt::cpp17::any_cast<Wt::WDate>(value(kEndDate)),
      Wt::cpp17::any_cast<Wt::WTime>(value(kEndTime))));

  event->set_is_reccurent(Wt::cpp17::any_cast<bool>(value(kIsRecurrent)));
  event->set_frequency(Wt::asString(value(kFrequency)));
  event->set_interval(Wt::cpp17::any_cast<std::size_t>(value(kInterval)));
  event->set_until(Wt::cpp17::any_cast<Wt::WDate>(value(kEndDate)));

  return event;
}

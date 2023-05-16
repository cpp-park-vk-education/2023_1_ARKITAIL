#include "event_model.hpp"

#include <memory>

#include <Wt/WAny.h>
#include <Wt/WDateValidator.h>
#include <Wt/WFormModel.h>
#include <Wt/WLengthValidator.h>
#include <Wt/WString.h>
#include <Wt/WTime.h>
#include <Wt/WTimeValidator.h>
#include <Wt/WValidator.h>

const Wt::WFormModel::Field EventModel::kTitle = "title";
const Wt::WFormModel::Field EventModel::kDescription= "description";
const Wt::WFormModel::Field EventModel::kCalendars = "calendars";

const Wt::WFormModel::Field EventModel::kBeginDate = "begin-date";
const Wt::WFormModel::Field EventModel::kBeginTime = "begin-time";
const Wt::WFormModel::Field EventModel::kEndDate = "end-date";
const Wt::WFormModel::Field EventModel::kEndTime = "end-time";

const Wt::WFormModel::Field EventModel::kRepeat = "repeat";
const Wt::WFormModel::Field EventModel::kUntil = "until";

// по умолчаню event = nullptr
EventModel::EventModel(
    std::shared_ptr<Event> event) : Wt::WFormModel() {
  addField(kTitle);
  addField(kDescription);
  addField(kCalendars);

  addField(kBeginDate);
  addField(kBeginTime);
  addField(kEndDate);
  addField(kEndTime);

  addField(kRepeat);
  addField(kUntil);

  setValidator(kTitle, CreateTitleValidator());
  setValidator(kBeginDate, CreateDateValidator());
  setValidator(kBeginTime, CreateTimeValidator());
  setValidator(kEndDate, CreateDateValidator());
  setValidator(kEndTime, CreateTimeValidator());
  setValidator(kUntil, CreateDateValidator());

  if (event) {
    setValue(kTitle, event->title);
    setValue(kDescription, event->description);
    setValue(kCalendars, event->calendar);

    setValue(kBeginDate, event->begin_date);
    setValue(kBeginTime, event->begin_time);
    setValue(kEndDate, event->end_date);
    setValue(kEndTime, event->end_time);

    setValue(kRepeat, event->repeat);
    setValue(kUntil, event->until);
  } else {
    // ...
  }
}

std::shared_ptr<Wt::WValidator> EventModel::CreateTitleValidator() {
  auto validator = std::make_shared<Wt::WLengthValidator>();

  validator->setMandatory(true);
  validator->setMinimumLength(1);
  validator->setMaximumLength(50);

  return validator;
}

std::shared_ptr<Wt::WValidator> EventModel::CreateDateValidator() {
  auto validator = std::make_shared<Wt::WDateValidator>();

  validator->setMandatory(true);
  validator->setFormat("dd.MM.yyyy");
  validator->setInvalidNotADateText("Введите дату в формате ДД.ММ.ГГГГ");
  validator->setInvalidBlankText("Дата не может быть пустой");

  return validator;
}

std::shared_ptr<Wt::WValidator> EventModel::CreateTimeValidator() {
  auto validator = std::make_shared<Wt::WTimeValidator>();

  validator->setMandatory(true);
  validator->setInvalidNotATimeText("Введите время в формате ЧЧ:ММ:СС");
  validator->setInvalidBlankText("Дата не может быть пустой");

  return validator;
}

std::shared_ptr<Event> EventModel::GetData() const {
  auto event = std::make_shared<Event>();

  event->title = Wt::asString(value(kTitle));
  event->description = Wt::asString(value(kDescription));
  event->calendar = Wt::asString(value(kCalendars));

  event->begin_date = Wt::asString(value(kBeginDate));
  event->begin_time = Wt::asString(value(kBeginTime));
  event->end_date = Wt::asString(value(kEndDate));
  event->end_time = Wt::asString(value(kEndTime));
  event->repeat = Wt::asString(value(kRepeat));
  event->until = Wt::asString(value(kUntil));

  return event;
}

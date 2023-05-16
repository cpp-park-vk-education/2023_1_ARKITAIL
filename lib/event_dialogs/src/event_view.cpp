#include "event_view.hpp"

#include <Wt/WComboBox.h>
#include <memory>
#include <vector>

#include <Wt/WDateEdit.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WTextArea.h>
#include <Wt/WTime.h>
#include <Wt/WTimeEdit.h>

#include "calendar.hpp"
#include "event.hpp"
#include "event_model.hpp"

// по умолчаню event = nullptr
EventView::EventView(
    std::vector<std::shared_ptr<Calendar>> public_calendars,
    std::vector<std::shared_ptr<Calendar>> private_calendars,
    std::shared_ptr<Event> event) {
  model_ = std::make_shared<EventModel>(event);

  setTemplateText(Wt::WString::tr("event"));

  addFunction("id", &WTemplate::Functions::id);

  auto title = std::make_unique<Wt::WLineEdit>();
  title_ = title.get();
  setFormWidget(EventModel::kTitle, std::move(title));

  auto description = std::make_unique<Wt::WTextArea>();
  description_ = description.get();
  setFormWidget(EventModel::kDescription, std::move(description));

  auto calendars = std::make_unique<Wt::WComboBox>();
  for (auto calendar : public_calendars) {
    calendars->addItem(calendar->title);
  }
  for (auto calendar : private_calendars) {
    calendars->addItem(calendar->title);
  }
  calendars_ = calendars.get();
  setFormWidget(EventModel::kCalendars, std::move(calendars));

  auto begin_date = std::make_unique<Wt::WDateEdit>();
  begin_date_ = begin_date.get();
  setFormWidget(EventModel::kBeginDate, std::move(begin_date));

  auto begin_time = std::make_unique<Wt::WTimeEdit>();
  begin_time_ = begin_time.get();
  setFormWidget(EventModel::kBeginTime, std::move(begin_time));

  auto end_date = std::make_unique<Wt::WDateEdit>();
  end_date_ = end_date.get();
  setFormWidget(EventModel::kEndDate, std::move(end_date));

  auto end_time = std::make_unique<Wt::WTimeEdit>();
  end_time_ = end_time.get();
  setFormWidget(EventModel::kEndTime, std::move(end_time));

  auto repeat = std::make_unique<Wt::WComboBox>();
  repeat->addItem("Не повторять");
  repeat->addItem("Ежедневно");
  repeat->addItem("По неделям");
  repeat->addItem("По месяцам");
  repeat->addItem("По годам");
  repeat_ = repeat.get();
  setFormWidget(EventModel::kRepeat, std::move(repeat));

  auto until = std::make_unique<Wt::WDateEdit>();
  until_ = until.get();
  setFormWidget(EventModel::kUntil, std::move(until));

  button_ = bindWidget(
      "submit-button", std::make_unique<Wt::WPushButton>("OK"));
  bindString("submit-info", Wt::WString());
  button_->addStyleClass("btn btn-success");
  button_->clicked().connect(this, &EventView::HandleInput);

  updateView(model_.get());
}

void EventView::HandleInput() {
  updateModel(model_.get());

  if (model_->validate()) {
    // ...
    event_created_.emit(model_->GetData());
    bindString("submit-info", Wt::WString("Успешно!"));
  } else {
    bindEmpty("submit-info");
  }

  updateView(model_.get());
}

Wt::Signal<std::shared_ptr<Event>>& EventView::event_created() {
  return event_created_;
}

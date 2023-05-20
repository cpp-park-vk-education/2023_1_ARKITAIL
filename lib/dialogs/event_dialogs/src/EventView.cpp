#include "EventView.hpp"

#include <memory>
#include <vector>

#include <Wt/WCheckBox.h>
#include <Wt/WComboBox.h>
#include <Wt/WDateEdit.h>
#include <Wt/WGlobal.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WTextArea.h>
#include <Wt/WTime.h>
#include <Wt/WTimeEdit.h>

#include "Calendar.hpp"
#include "Event.hpp"
#include "EventModel.hpp"

// по умолчаню event = nullptr
EventView::EventView(
    std::vector<std::shared_ptr<Calendar>> public_calendars,
    std::vector<std::shared_ptr<Calendar>> private_calendars,
    std::shared_ptr<Event> event) {
  model_ = std::make_shared<EventModel>(event);

  setTemplateText(Wt::WString::tr("event"));

  addFunction("id", &WTemplate::Functions::id);

  auto summary = std::make_unique<Wt::WLineEdit>();
  summary_ = summary.get();
  setFormWidget(EventModel::kSummary, std::move(summary));

  auto description = std::make_unique<Wt::WTextArea>();
  description_ = description.get();
  setFormWidget(EventModel::kDescription, std::move(description));

  auto calendars = std::make_unique<Wt::WComboBox>();
  for (auto calendar : public_calendars) {
    calendars->addItem(calendar->summary());
  }
  for (auto calendar : private_calendars) {
    calendars->addItem(calendar->summary());
  }
  calendars_ = calendars.get();
  setFormWidget(EventModel::kCalendars, std::move(calendars));

  auto start_date = std::make_unique<Wt::WDateEdit>();
  start_date_ = start_date.get();
  setFormWidget(EventModel::kStartDate, std::move(start_date));

  auto begin_time = std::make_unique<Wt::WTimeEdit>();
  start_time_ = begin_time.get();
  setFormWidget(EventModel::kStartTime, std::move(begin_time));

  auto end_date = std::make_unique<Wt::WDateEdit>();
  end_date_ = end_date.get();
  setFormWidget(EventModel::kEndDate, std::move(end_date));

  auto end_time = std::make_unique<Wt::WTimeEdit>();
  end_time_ = end_time.get();
  setFormWidget(EventModel::kEndTime, std::move(end_time));

  auto is_all_day = std::make_unique<Wt::WCheckBox>("Весь день");
  is_all_day_ = is_all_day.get();
  is_all_day_->changed().connect([=] {
    if (is_all_day_->checkState() == Wt::CheckState::Checked) {
      start_time_->setEnabled(false);
      end_time_->setEnabled(false);
    } else if (is_all_day_->checkState() == Wt::CheckState::Unchecked) {
      start_time_->setEnabled(true);
      end_time_->setEnabled(true);
    }
  });
  setFormWidget(EventModel::kIsAllDay, std::move(is_all_day));

  auto is_recurrent = std::make_unique<Wt::WCheckBox>("Повторять");
  is_recurrent_ = is_recurrent.get();
  is_recurrent_->changed().connect([=] {
    if (is_recurrent_->checkState() == Wt::CheckState::Checked) {
      frequency_->setEnabled(true);
      interval_->setEnabled(true);
      until_->setEnabled(true);
    } else if (is_recurrent_->checkState() == Wt::CheckState::Unchecked) {
      frequency_->setEnabled(false);
      interval_->setEnabled(false);
      until_->setEnabled(false);
    }
  });
  setFormWidget(EventModel::kIsRecurrent, std::move(is_recurrent));

  auto frequency = std::make_unique<Wt::WComboBox>();
  frequency->addItem("По дням");
  frequency->addItem("По неделям");
  frequency->addItem("По месяцам");
  frequency->addItem("По годам");
  frequency_ = frequency.get();
  setFormWidget(EventModel::kFrequency, std::move(frequency));

  auto interval = std::make_unique<Wt::WSpinBox>();
  interval_ = interval.get();
  setFormWidget(EventModel::kInterval, std::move(interval));

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

#include "EventView.hpp"

#include <memory>

#include <Wt/WCheckBox.h>
#include <Wt/WComboBox.h>
#include <Wt/WDateEdit.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTextArea.h>
#include <Wt/WTime.h>
#include <Wt/WTimeEdit.h>

#include "Calendar.hpp"
#include "Event.hpp"
#include "EventModel.hpp"

namespace dialog {
EventView::EventView(std::shared_ptr<EventModel> model)
    : model_(model) {
  setTemplateText(Wt::WString::tr("event"));

  addFunction("id", &WTemplate::Functions::id);

  InitializeSummary();
  InitializeDescription();
  InitializeCalendars();
  InitializeStartDate();
  InitializeStartTime();
  InitializeEndDate();
  InitializeEndTime();
  InitializeIsRecurrent();
  InitializeFrequency();
  InitializeInterval();
  InitializeUntil();
  InitializeButton();

  updateView(model_.get());
}

void EventView::InitializeSummary() {
  auto summary = std::make_unique<Wt::WLineEdit>();
  summary_ = summary.get();
  setFormWidget(EventModel::kSummary, std::move(summary));
}

void EventView::InitializeDescription() {
  auto description = std::make_unique<Wt::WTextArea>();
  description_ = description.get();
  setFormWidget(EventModel::kDescription, std::move(description));
}

void EventView::InitializeCalendars() {
  auto calendars = std::make_unique<Wt::WComboBox>();
  // TODO(affeeal): разобраться с event->calendars
  calendars_ = calendars.get();
  setFormWidget(EventModel::kCalendars, std::move(calendars));
}

void EventView::InitializeStartDate() {
  auto start_date = std::make_unique<Wt::WDateEdit>();
  start_date_ = start_date.get();
  setFormWidget(EventModel::kStartDate, std::move(start_date));
}

void EventView::InitializeStartTime() {
  auto start_time = std::make_unique<Wt::WTimeEdit>();
  start_time_ = start_time.get();
  setFormWidget(EventModel::kStartTime, std::move(start_time));
}

void EventView::InitializeEndDate() {
  auto end_date = std::make_unique<Wt::WDateEdit>();
  end_date_ = end_date.get();
  setFormWidget(EventModel::kEndDate, std::move(end_date));
}

void EventView::InitializeEndTime() {
  auto end_time = std::make_unique<Wt::WTimeEdit>();
  end_time_ = end_time.get();
  setFormWidget(EventModel::kEndTime, std::move(end_time));
}

void EventView::InitializeIsRecurrent() {
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
}

void EventView::InitializeFrequency() {
  auto frequency = std::make_unique<Wt::WComboBox>();
  frequency_ = frequency.get();
  frequency_->addItem("По дням");
  frequency_->addItem("По неделям");
  frequency_->addItem("По месяцам");
  frequency_->addItem("По годам");
  setFormWidget(EventModel::kFrequency, std::move(frequency));
}

void EventView::InitializeInterval() {
  auto interval = std::make_unique<Wt::WSpinBox>();
  interval_ = interval.get();
  setFormWidget(EventModel::kInterval, std::move(interval));
}

void EventView::InitializeUntil() {
  auto until = std::make_unique<Wt::WDateEdit>();
  until_ = until.get();
  setFormWidget(EventModel::kUntil, std::move(until));
}

void EventView::InitializeButton() {
}

void EventView::HandleInput() {
}
} // namespace dialog

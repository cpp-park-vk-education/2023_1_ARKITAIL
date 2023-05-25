#include "EventView.hpp"

#include <memory>

#include <Wt/WCheckBox.h>
#include <Wt/WComboBox.h>
#include <Wt/WDateEdit.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WTextArea.h>
#include <Wt/WTime.h>
#include <Wt/WTimeEdit.h>

#include "Calendar.hpp"
#include "Event.hpp"
#include "EventModel.hpp"

namespace dialog {
std::shared_ptr<EventModel> EventView::model() const {
  return model_;
}

// по умолчанию event = nullptr
EventView::EventView(EventSptr event)
    : Wt::WTemplateFormView(Wt::WString::tr("event")),
      model_(std::make_shared<EventModel>(event)) {
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

  bindEmpty("validation-status");

  updateView(model_.get());
}

void EventView::InitializeSummary() {
  setFormWidget(EventModel::kSummary, std::make_unique<Wt::WLineEdit>());
}

void EventView::InitializeDescription() {
  setFormWidget(EventModel::kDescription, std::make_unique<Wt::WTextArea>());
}

void EventView::InitializeCalendars() {
  auto calendars = std::make_unique<Wt::WComboBox>();
  // TODO(affeeal): разобраться с calendars
  setFormWidget(EventModel::kCalendars, std::move(calendars));
}

void EventView::InitializeStartDate() {
  setFormWidget(EventModel::kStartDate, std::make_unique<Wt::WDateEdit>());
}

void EventView::InitializeStartTime() {
  setFormWidget(EventModel::kStartTime, std::make_unique<Wt::WTimeEdit>());
}

void EventView::InitializeEndDate() {
  setFormWidget(EventModel::kEndDate, std::make_unique<Wt::WDateEdit>());
}

void EventView::InitializeEndTime() {
  setFormWidget(EventModel::kEndTime, std::make_unique<Wt::WTimeEdit>());
}

void EventView::InitializeIsRecurrent() {
  auto is_recurrent = std::make_unique<Wt::WCheckBox>("Повторять");
  is_recurrent_ = is_recurrent.get();
  is_recurrent->changed().connect([=] {
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
} // namespace dialog

#pragma once

#include <memory>

#include <Wt/WCheckBox.h>
#include <Wt/WComboBox.h>
#include <Wt/WDateEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WSpinBox.h>
#include <Wt/WTemplateFormView.h>

#include "Event.hpp"
#include "EventModel.hpp"

namespace dialog {
class EventView : public Wt::WTemplateFormView {
 public:
  std::shared_ptr<EventModel> model() const;

  explicit EventView(EventSptr event = nullptr);
 private:
  void InitializeSummary();
  void InitializeDescription();
  void InitializeLocation();
  void InitializeCalendars();
  void InitializeStartDate();
  void InitializeStartTime();
  void InitializeEndDate();
  void InitializeEndTime();
  void InitializeIsRecurrent();
  void InitializeFrequency();
  void InitializeInterval();
  void InitializeUntil();

  std::shared_ptr<EventModel> model_;

  Wt::WCheckBox* is_recurrent_;
  Wt::WComboBox* frequency_;
  Wt::WSpinBox* interval_;
  Wt::WDateEdit* until_;
};
} // namespace dialog

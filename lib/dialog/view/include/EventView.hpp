#pragma once

#include <memory>

#include <Wt/WComboBox.h>
#include <Wt/WDateEdit.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WSpinBox.h>
#include <Wt/WTemplateFormView.h>
#include <Wt/WTextArea.h>
#include <Wt/WTimeEdit.h>

#include "Event.hpp"
#include "EventModel.hpp"

namespace dialog {
class EventView : public Wt::WTemplateFormView {
 protected:
  EventView() = delete;
  explicit EventView(std::shared_ptr<EventModel> model);

  void InitializeSummary();
  void InitializeDescription();
  void InitializeCalendars();
  void InitializeStartDate();
  void InitializeStartTime();
  void InitializeEndDate();
  void InitializeEndTime();
  void InitializeIsRecurrent();
  void InitializeFrequency();
  void InitializeInterval();
  void InitializeUntil();
  virtual void InitializeButton();

  virtual void HandleInput();

  std::shared_ptr<EventModel> model_;

  Wt::WLineEdit* summary_;
  Wt::WTextArea* description_;
  Wt::WComboBox* calendars_;
  Wt::WDateEdit* start_date_;
  Wt::WTimeEdit* start_time_;
  Wt::WDateEdit* end_date_;
  Wt::WTimeEdit* end_time_;
  Wt::WCheckBox* is_recurrent_;
  Wt::WComboBox* frequency_;
  Wt::WSpinBox* interval_;
  Wt::WDateEdit* until_;
  Wt::WPushButton* button_;
};
} // namespace dialog

#pragma once

#include <memory>
#include <vector>

#include <Wt/WComboBox.h>
#include <Wt/WDateEdit.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WSpinBox.h>
#include <Wt/WTemplateFormView.h>
#include <Wt/WTextArea.h>
#include <Wt/WTimeEdit.h>

#include "Calendar.hpp"
#include "Event.hpp"
#include "EventModel.hpp"

class EventView : public Wt::WTemplateFormView {
 public:
  EventView(
      std::vector<std::shared_ptr<Calendar>> public_calendars,
      std::vector<std::shared_ptr<Calendar>> private_calendars,
      std::shared_ptr<Event> event = nullptr);

  Wt::Signal<std::shared_ptr<Event>>& event_created();
 private:
  void HandleInput();
  
  std::shared_ptr<EventModel> model_;
  
  Wt::WLineEdit* summary_;
  Wt::WTextArea* description_;
  Wt::WComboBox* calendars_;

  Wt::WDateEdit* start_date_;
  Wt::WTimeEdit* start_time_;
  Wt::WDateEdit* end_date_;
  Wt::WTimeEdit* end_time_;
  Wt::WCheckBox* is_all_day_;
  
  Wt::WCheckBox* is_recurrent_;
  Wt::WComboBox* frequency_;
  Wt::WSpinBox* interval_;
  Wt::WDateEdit* until_;

  Wt::WPushButton* button_;

  Wt::Signal<std::shared_ptr<Event>> event_created_;
};

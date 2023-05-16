#pragma once

#include <memory>
#include <vector>

#include <Wt/WComboBox.h>
#include <Wt/WDateEdit.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplateFormView.h>
#include <Wt/WTextArea.h>
#include <Wt/WTimeEdit.h>

#include "calendar.hpp"
#include "event.hpp"
#include "event_model.hpp"

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
  
  Wt::WLineEdit* title_;
  Wt::WTextArea* description_;
  Wt::WComboBox* calendars_;

  Wt::WDateEdit* begin_date_;
  Wt::WTimeEdit* begin_time_;
  Wt::WDateEdit* end_date_;
  Wt::WTimeEdit* end_time_;
  
  Wt::WComboBox* repeat_;
  Wt::WDateEdit* until_;

  Wt::WPushButton* button_;

  Wt::Signal<std::shared_ptr<Event>> event_created_;
};

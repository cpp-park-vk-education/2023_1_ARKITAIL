#pragma once

#include <Wt/WDialog.h>

#include "EventView.hpp"
#include "Event.hpp"

namespace dialog {
class CreateEventDialog : public Wt::WDialog {
 public:
  CreateEventDialog();

  Wt::Signal<EventSptr>& event_created();
 private:
  void HandleInput();

  Wt::Signal<EventSptr> event_created_;

  EventView* view_;
};
} // namespace dialog

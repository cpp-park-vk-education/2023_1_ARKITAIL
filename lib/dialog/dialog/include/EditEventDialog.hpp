#pragma once

#include <Wt/WDialog.h>

#include "EventView.hpp"
#include "Event.hpp"

namespace dialog {
class EditEventDialog : public Wt::WDialog {
 public:
  EditEventDialog() = delete;
  EditEventDialog(EventSptr event);

  Wt::Signal<EventSptr>& event_updated();
 private:
  void HandleInput();

  Wt::Signal<EventSptr> event_updated_;

  EventView* view_;
};
} // namespace dialog

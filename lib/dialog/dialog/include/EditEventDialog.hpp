#pragma once

#include <Wt/WDialog.h>

#include "EditEventView.hpp"
#include "Event.hpp"

namespace dialog {
class EditEventDialog : public Wt::WDialog {
 public:
  EditEventDialog(EventSptr event);

  Wt::Signal<EventSptr>& event_updated();
 private:
  void HandleInput();

  Wt::Signal<EventSptr> event_updated_;

  EditEventView* view_;
};
} // namespace dialog

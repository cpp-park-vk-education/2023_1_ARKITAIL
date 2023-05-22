#pragma once

#include "Event.hpp"
#include "EventView.hpp"

namespace dialog {
class EditEventView : public EventView {
 public:
  EditEventView(EventSptr event);

  Wt::Signal<EventSptr>& event_updated();
 private:
  void InitializeButton() override;

  void HandleInput() override;

  Wt::Signal<EventSptr> event_updated_;
};
} // namespace dialog

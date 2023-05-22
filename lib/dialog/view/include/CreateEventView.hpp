#pragma once

#include "Event.hpp"
#include "EventView.hpp"

namespace dialog {
class CreateEventView : public EventView {
 public:
  CreateEventView();

  Wt::Signal<EventSptr>& event_created();
 private:
  void InitializeButton() override;

  void HandleInput() override;

  Wt::Signal<EventSptr> event_created_;
};
} // namespace dialog

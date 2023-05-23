#pragma once

#include "Event.hpp"
#include "EventView.hpp"

namespace dialog {
class EditEventView : public EventView {
 public:
  explicit EditEventView(EventSptr event);
};
} // namespace dialog

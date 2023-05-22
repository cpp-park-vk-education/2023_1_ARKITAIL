#pragma once

#include <Wt/WObject.h>

#include "Dialog.hpp"
#include "Event.hpp"

namespace dialog {
class EditEventDialog : public Dialog {
 public:
  EditEventDialog(Wt::WObject* parent, EventSptr event);
};
} // namespace dialog

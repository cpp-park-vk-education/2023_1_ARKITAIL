#pragma once

#include "Wt/WObject.h"

#include "Dialog.hpp"

namespace dialog {
class CreateEventDialog : public Dialog {
 public:
  CreateEventDialog(Wt::WObject* parent);
};
} // namespace dialog

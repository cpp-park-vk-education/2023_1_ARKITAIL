#pragma once

#include "Wt/WObject.h"

#include "Dialog.hpp"

namespace dialog {
class CreateCalendarDialog : public Dialog {
 public:
  CreateCalendarDialog(Wt::WObject* parent);
};
} // namespace dialog

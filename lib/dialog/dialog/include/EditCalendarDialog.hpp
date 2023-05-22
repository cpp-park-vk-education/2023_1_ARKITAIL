#pragma once

#include <Wt/WObject.h>

#include "Calendar.hpp"
#include "Dialog.hpp"

namespace dialog {
class EditCalendarDialog : public Dialog {
 public:
  EditCalendarDialog(Wt::WObject* parent, CalendarSptr calendar);
};
} // namespace dialog

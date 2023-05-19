#pragma once

#include <Wt/WObject.h>

#include "calendar_dialog.hpp"

class CreateCalendarDialog : protected CalendarDialog {
 public:
   static void Show(Wt::WObject* parent);
};

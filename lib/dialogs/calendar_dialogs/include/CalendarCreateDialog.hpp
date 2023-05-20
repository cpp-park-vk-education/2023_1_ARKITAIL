#pragma once

#include <Wt/WObject.h>

#include "CalendarDialog.hpp"

class CreateCalendarDialog : protected CalendarDialog {
 public:
   static void Show(Wt::WObject* parent);
};

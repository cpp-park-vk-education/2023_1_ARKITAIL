#pragma once

#include <memory>

#include <Wt/WObject.h>

#include "calendar.hpp"
#include "calendar_dialog.hpp"

class EditCalendarDialog : private CalendarDialog {
 public:
   static void Show(
       Wt::WObject* parent,
       CalendarSptr calendar);
};

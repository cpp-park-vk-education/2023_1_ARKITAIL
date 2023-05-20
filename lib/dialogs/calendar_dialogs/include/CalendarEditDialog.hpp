#pragma once

#include <memory>

#include <Wt/WObject.h>

#include "Calendar.hpp"
#include "CalendarDialog.hpp"

class EditCalendarDialog : private CalendarDialog {
 public:
   static void Show(
       Wt::WObject* parent,
       CalendarSptr calendar);
};

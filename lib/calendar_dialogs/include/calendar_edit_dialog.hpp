#pragma once

#include <Wt/WObject.h>

#include "calendar.hpp"

class EditCalendarDialog {
 public:
   static void Show(Wt::WObject* parent, std::shared_ptr<Calendar> calendar);
};

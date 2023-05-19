#pragma once

#include <memory>

#include <Wt/WObject.h>
#include <Wt/WWidget.h>

class CalendarDialog {
 protected:
   static void ShowInternal(
       Wt::WObject* parent,
       std::unique_ptr<Wt::WWidget>&& contents);
};

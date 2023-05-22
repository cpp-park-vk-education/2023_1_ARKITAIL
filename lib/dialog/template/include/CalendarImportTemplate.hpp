#pragma once

#include <Wt/WFileUpload.h>
#include <Wt/WTemplate.h>

#include "Calendar.hpp"

namespace dialog {
class CalendarImportTemplate : public Wt::WTemplate {
 public:
  CalendarImportTemplate();

  Wt::Signal<CalendarSptr>& calendar_created();
 private:
  void HandleInput();

  Wt::WFileUpload* import_icalendar_;
  
  Wt::Signal<CalendarSptr> calendar_created_;
};
} // namespace dialog

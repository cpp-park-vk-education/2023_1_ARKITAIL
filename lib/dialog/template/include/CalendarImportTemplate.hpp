#pragma once

#include <Wt/WFileUpload.h>
#include <Wt/WTemplate.h>

namespace dialog {
class CalendarImportTemplate : public Wt::WTemplate {
 public:
  CalendarImportTemplate();

  Wt::WFileUpload* import_icalendar();
 private:
  Wt::WFileUpload* import_icalendar_;
};
} // namespace dialog

#include "CalendarImportTemplate.hpp"

#include <Wt/WFileUpload.h>
#include <Wt/WPushButton.h>

namespace dialog {
CalendarImportTemplate::CalendarImportTemplate()
    : Wt::WTemplate(Wt::WString::tr("calendar-import")) {
  auto import_icalendar = std::make_unique<Wt::WFileUpload>();
  import_icalendar_ = import_icalendar.get();
  import_icalendar_->changed().connect([=] {
    if (import_icalendar_->canUpload()) {
      import_icalendar_->upload();
    }
  });
  bindWidget("import-icalendar", std::move(import_icalendar));
  bindEmpty("validation-status");
}

Wt::WFileUpload* CalendarImportTemplate::import_icalendar() const {
  return import_icalendar_;
}
} // namespace dialog

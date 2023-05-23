#include "CalendarImportTemplate.hpp"

#include <Wt/WFileUpload.h>
#include <Wt/WPushButton.h>

namespace dialog {
CalendarImportTemplate::CalendarImportTemplate()
    : Wt::WTemplate(Wt::WString::tr("calendar-import")) {
  // возможно, строка ниже избыточна
  addFunction("id", &Wt::WTemplate::Functions::id);

  auto import_icalendar = std::make_unique<Wt::WFileUpload>();
  import_icalendar_ = import_icalendar.get();
  // стоит вынести лямбду в отдельный метод класса
  import_icalendar_->changed().connect([=] {
    if (import_icalendar_->canUpload()) {
      import_icalendar_->upload();
    }
  });
  bindWidget("import-icalendar", std::move(import_icalendar));
}

Wt::WFileUpload* CalendarImportTemplate::import_icalendar() {
  return import_icalendar_;
}
} // namespace dialog

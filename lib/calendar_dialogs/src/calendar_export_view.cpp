#include "calendar_export_view.hpp"

#include <memory>

#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplateFormView.h>

#include "calendar_export_model.hpp"

CalendarExportView::CalendarExportView(std::shared_ptr<Calendar> calendar) {
  model_ = std::make_shared<CalendarExportModel>(calendar);

  setTemplateText(Wt::WString::tr("calendar-export"));

  addFunction("id", &Wt::WTemplate::Functions::id);

  auto export_iCalendar = std::make_unique<Wt::WLineEdit>();
  export_iCalendar_ = export_iCalendar.get();
  setFormWidget(
      CalendarExportModel::kExportiCalendarField, std::move(export_iCalendar));
  
  updateView(model_.get());
}

#include "calendar_export_model.hpp"

#include <Wt/WFormModel.h>

const Wt::WFormModel::Field CalendarExportModel::kExportiCalendarField
  = "export-icalendar";

CalendarExportModel::CalendarExportModel(std::shared_ptr<Calendar> calendar) {
  addField(kExportiCalendarField);

  // TODO(affeeal): преобразование calendar в Wt::WResource
  setValue(kExportiCalendarField, "здесь будет ссылка на скачивание...");
}

#include "calendar_import_model.hpp"

#include <Wt/WFormModel.h>

const Wt::WFormModel::Field CalendarImportModel::kImportiCalendarField
  = "import-icalendar";

CalendarImportModel::CalendarImportModel() {
  addField(kImportiCalendarField);
}

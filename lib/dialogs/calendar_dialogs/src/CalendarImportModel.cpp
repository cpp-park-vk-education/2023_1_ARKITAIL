#include "CalendarImportModel.hpp"

#include <Wt/WFormModel.h>

const Wt::WFormModel::Field CalendarImportModel::kImportIcalendar
  = "import-icalendar";

CalendarImportModel::CalendarImportModel() {
  addField(kImportIcalendar);
}

#include "CalendarExportTemplate.hpp"

#include <Wt/WLogger.h>
#include <sstream>

#include <Wt/WAnchor.h>
#include <Wt/WLink.h>
#include <Wt/WTemplate.h>

#include "Calendar.hpp"
#include "CalendarConverter.hpp"
#include "StringStreamResource.hpp"

namespace dialog {
CalendarExportTemplate::CalendarExportTemplate(CalendarSptr calendar)
    : Wt::WTemplate(Wt::WString::tr("calendar-export")) {
  std::stringstream ss = CalendarConverter::CalendarToIcalendar(calendar);
  
  auto resource = std::make_shared<StringStreamResource>(std::move(ss));
  Wt::WLink link(resource);
  auto anchor = std::make_unique<Wt::WAnchor>(
      link, "Скачать в формате iCalendar");

  bindWidget("export-icalendar", std::move(anchor));
}
} // namespace dialog

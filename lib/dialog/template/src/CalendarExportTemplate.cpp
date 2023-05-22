#include "CalendarExportTemplate.hpp"

#include <sstream>

#include <Wt/WAnchor.h>
#include <Wt/WLink.h>
#include <Wt/WString.h>
#include <Wt/WTemplate.h>

#include "Calendar.hpp"
#include "CalendarConverter.hpp"
#include "StringStreamResource.hpp"
#include "IstreamCharacterReader.hpp"

namespace dialog {
CalendarExportTemplate::CalendarExportTemplate(CalendarSptr calendar)
    : Wt::WTemplate(Wt::WString::tr("calendar-export")) {
  CalendarConverter converter;
  auto buffer = converter.CalendarsToIcalendar(
      std::vector<size_t> { calendar->id });
  auto resource = std::make_shared<StringStreamResource>(std::move(buffer));
  Wt::WLink link(resource);
  auto anchor = std::make_unique<Wt::WAnchor>(
      link,
      "Скачать в формате iCalendar");
  bindWidget("export-icalendar", std::move(anchor));
}
} // namespace dialog

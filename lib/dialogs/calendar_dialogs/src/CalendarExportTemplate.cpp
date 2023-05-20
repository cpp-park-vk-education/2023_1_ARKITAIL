#include "CalendarExportTemplate.hpp"

#include <sstream>

#include <Wt/WAnchor.h>
#include <Wt/WLink.h>
#include <Wt/WString.h>
#include <Wt/WTemplate.h>

#include "Calendar.hpp"
#include "CalendarConverter.hpp"
#include "StringStreamResource.hpp"

CalendarExportTemplate::CalendarExportTemplate(CalendarSptr calendar)
    : Wt::WTemplate(Wt::WString::tr("calendar-export")) {
  CalendarConverter converter;
  auto char_reader = converter.CalendarToIcalendar(
      std::vector<CalendarSptr> { calendar });
  auto resource = std::make_shared<StringStreamResource>(std::move(char_reader));
  Wt::WLink link(resource);
  auto anchor = std::make_unique<Wt::WAnchor>(
      link,
      "Скачать в формате iCalendar");
  bindWidget("export-icalendar", std::move(anchor));
}

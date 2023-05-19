#include "calendar_export_template.hpp"

#include <sstream>

#include <Wt/WAnchor.h>
#include <Wt/WLink.h>
#include <Wt/WString.h>
#include <Wt/WTemplate.h>

#include "string_stream_resource.hpp"

CalendarExportTemplate::CalendarExportTemplate(const std::string& key)
    : Wt::WTemplate(Wt::WString::tr(key)) {
  // ...
  std::stringstream ss;
  auto resource = std::make_shared<StringStreamResource>(std::move(ss));
  Wt::WLink link(resource);
  auto anchor = std::make_unique<Wt::WAnchor>(
      link,
      "Скачать в формате iCalendar");
  bindWidget("export-icalendar", std::move(anchor));
}

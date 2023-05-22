#pragma once

#include <string>

#include <Wt/WTemplate.h>

#include "Calendar.hpp"

namespace dialog {
class CalendarExportTemplate : public Wt::WTemplate {
 public:
  CalendarExportTemplate(CalendarSptr calendar);
};
} // namespace dialog

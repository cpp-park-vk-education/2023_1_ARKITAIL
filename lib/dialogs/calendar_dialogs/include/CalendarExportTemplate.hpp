#pragma once

#include <string>

#include <Wt/WTemplate.h>

#include "Calendar.hpp"

class CalendarExportTemplate : public Wt::WTemplate {
 public:
  CalendarExportTemplate(CalendarSptr calendar);
};

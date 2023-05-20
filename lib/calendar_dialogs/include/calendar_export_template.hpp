#pragma once

#include <string>

#include <Wt/WTemplate.h>

#include "calendar.hpp"

class CalendarExportTemplate : public Wt::WTemplate {
 public:
  CalendarExportTemplate(CalendarSptr calendar);
};

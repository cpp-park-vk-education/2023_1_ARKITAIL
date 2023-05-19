#pragma once

#include <string>

#include <Wt/WTemplate.h>

class CalendarExportTemplate : public Wt::WTemplate {
 public:
  CalendarExportTemplate(const std::string& key);
};

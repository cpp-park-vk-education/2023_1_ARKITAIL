#pragma once

#include <memory>

#include <Wt/WFormModel.h>

#include "calendar.hpp"

class CalendarExportModel : public Wt::WFormModel {
 public:
  static const Wt::WFormModel::Field kExportiCalendarField;

  CalendarExportModel(std::shared_ptr<Calendar> calendar);
};

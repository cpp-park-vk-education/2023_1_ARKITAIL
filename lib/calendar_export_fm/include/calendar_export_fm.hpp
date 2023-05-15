#pragma once

#include <memory>

#include <Wt/WFormModel.h>

#include "calendar.hpp"

class CalendarExportFM : public Wt::WFormModel {
 public:
  static const Wt::WFormModel::Field kExportiCalendarField;

  CalendarExportFM();

  void SetData(std::unique_ptr<Calendar> calendar);
};

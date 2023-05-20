#pragma once

#include <memory>

#include <Wt/WFormModel.h>

#include "Calendar.hpp"

class CalendarImportModel : public Wt::WFormModel {
 public:
  static const Wt::WFormModel::Field kImportIcalendar;

  CalendarImportModel();
};

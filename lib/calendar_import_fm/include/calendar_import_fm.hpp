#pragma once

#include <memory>

#include <Wt/WFormModel.h>

#include "calendar.hpp"

class CalendarImportFM : public Wt::WFormModel {
 public:
  static const Wt::WFormModel::Field kImportiCalendarField;

  CalendarImportFM();

  std::unique_ptr<Calendar> GetData();
};

#pragma once

#include <memory>

#include <Wt/WFormModel.h>

#include "calendar.hpp"

class CalendarImportModel : public Wt::WFormModel {
 public:
  static const Wt::WFormModel::Field kImportiCalendarField;

  CalendarImportModel();

  std::shared_ptr<Calendar> GetData() const;
};

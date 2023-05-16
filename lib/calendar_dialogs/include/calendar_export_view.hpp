#pragma once

#include <memory>

#include <Wt/WTemplateFormView.h>
#include <Wt/WLineEdit.h>

#include "calendar.hpp"
#include "calendar_export_fm.hpp"

class CalendarExportFV : public Wt::WTemplateFormView {
 public:
  CalendarExportFV();

  void UpdateModel(std::unique_ptr<Calendar> calendar);
 private:
  std::shared_ptr<CalendarExportFM> model_;
  
  Wt::WLineEdit* export_iCalendar_;
};

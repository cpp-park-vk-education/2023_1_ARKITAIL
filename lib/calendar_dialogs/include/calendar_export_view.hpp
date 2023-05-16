#pragma once

#include <memory>

#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplateFormView.h>

#include "calendar_export_model.hpp"

class CalendarExportView : public Wt::WTemplateFormView {
 public:
  CalendarExportView(std::shared_ptr<Calendar> calendar);
 private:
  std::shared_ptr<CalendarExportModel> model_;
  
  Wt::WLineEdit* export_iCalendar_;
};

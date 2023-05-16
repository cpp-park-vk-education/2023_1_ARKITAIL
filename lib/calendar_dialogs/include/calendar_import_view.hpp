#pragma once

#include <memory>

#include <Wt/WTemplateFormView.h>
#include <Wt/WFileUpload.h>

#include "calendar_import_model.hpp"

class CalendarImportView : public Wt::WTemplateFormView {
 public:
  CalendarImportView();

  void HandleInput();
 private:
  std::shared_ptr<CalendarImportModel> model_;
  
  Wt::WFileUpload* import_iCalendar_;
};

#pragma once

#include <memory>

#include <Wt/WTemplateFormView.h>
#include <Wt/WFileUpload.h>

#include "calendar_import_fm.hpp"

class CalendarImportFV : public Wt::WTemplateFormView {
 public:
  CalendarImportFV();

  void HandleInput();
 private:
  std::shared_ptr<CalendarImportFM> model_;
  
  Wt::WFileUpload* import_iCalendar_;
};

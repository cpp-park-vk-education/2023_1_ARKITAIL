#pragma once

#include <memory>

#include <Wt/WFileUpload.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplateFormView.h>

#include "calendar_import_model.hpp"

class CalendarImportView : public Wt::WTemplateFormView {
 public:
  CalendarImportView();

  Wt::Signal<std::shared_ptr<Calendar>>& calendar_created();
 private:
  void HandleInput();

  std::shared_ptr<CalendarImportModel> model_;
  
  Wt::WFileUpload* import_iCalendar_;
  Wt::WPushButton* button_;

  Wt::Signal<std::shared_ptr<Calendar>> calendar_created_;
};

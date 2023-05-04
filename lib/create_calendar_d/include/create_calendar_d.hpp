#pragma once

#include <Wt/WDialog.h>
#include <Wt/WGlobal.h>

#include "calendar.hpp"
#include "calendar_settings_fv.hpp"
#include "calendar_import_fv.hpp"

class CreateCalendarD : public Wt::WDialog {
 public:
  CreateCalendarD();

  void Show();

  Wt::Signal<std::unique_ptr<Calendar>>& CalendarCreated();
 private:
  Wt::WTabWidget* tabs_;
  CalendarSettingsFV* calendar_settings_;
  CalendarImportFV* calendar_import_;

  Wt::WPushButton* create_;
  Wt::WPushButton* cancel_;

  Wt::Signal<std::unique_ptr<Calendar>> calendar_created_;
};

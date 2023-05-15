#pragma once

#include <Wt/WDialog.h>
#include <Wt/WGlobal.h>

#include "calendar.hpp"
#include "calendar_settings_fv.hpp"
#include "calendar_export_fv.hpp"

class EditCalendarD : public Wt::WDialog {
 public:
  EditCalendarD();

  void Show(std::unique_ptr<Calendar> calendar);

  Wt::Signal<std::unique_ptr<Calendar>>& CalendarEdited();
 private:
  Wt::WTabWidget* tabs_;
  CalendarSettingsFV* calendar_settings_;
  CalendarExportFV* calendar_export_;

  Wt::WPushButton* edit_;
  Wt::WPushButton* cancel_;

  Wt::Signal<std::unique_ptr<Calendar>> calendar_edited_;
};

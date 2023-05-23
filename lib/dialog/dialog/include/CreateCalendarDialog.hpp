#pragma once

#include <Wt/WDialog.h>
#include <Wt/WTabWidget.h>

#include "Calendar.hpp"

namespace dialog {
class CreateCalendarDialog : public Wt::WDialog {
 public:
  CreateCalendarDialog();

  Wt::Signal<CalendarSptr>& calendar_created();
 private:
  void ChooseHandler();

  void HandleSettings();
  void HandleImport();

  Wt::Signal<CalendarSptr> calendar_created_;

  Wt::WTabWidget* tabs_;
};
} // namespace dialog

#pragma once

#include <Wt/WDialog.h>
#include <Wt/WTabWidget.h>

#include "Calendar.hpp"

namespace dialog {
class EditCalendarDialog : public Wt::WDialog {
 public:
  EditCalendarDialog(CalendarSptr calendar);

  Wt::Signal<CalendarSptr>& calendar_updated();
 private:
  void ChooseHandler();

  void HandleSettings();

  Wt::Signal<CalendarSptr> calendar_updated_;

  Wt::WTabWidget* tabs_;
};
} // namespace dialog

#include "EditCalendarDialog.hpp"

#include <Wt/WObject.h>

#include <Wt/WTabWidget.h>

#include "Calendar.hpp"
#include "CalendarExportTemplate.hpp"
#include "EditCalendarView.hpp"

namespace dialog {
EditCalendarDialog::EditCalendarDialog(
    Wt::WObject* parent,
    CalendarSptr calendar) {
  parent_ = parent;

  auto tabs = std::make_unique<Wt::WTabWidget>();
  tabs->addTab(std::make_unique<EditCalendarView>(calendar), "Настройки");
  tabs->addTab(std::make_unique<CalendarExportTemplate>(calendar), "Экспорт");
  contents_ = std::move(tabs);

  title_ = "Календарь";
  min_width_ = 500;
  min_height_ = 500;
}
} // namespace dialog

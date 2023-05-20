#include "CalendarEditDialog.hpp"

#include <memory>

#include <Wt/WDialog.h>
#include <Wt/WObject.h>
#include <Wt/WTabWidget.h>

#include "Calendar.hpp"
#include "CalendarSettingsView.hpp"
#include "CalendarExportTemplate.hpp"

void EditCalendarDialog::Show(
    Wt::WObject* parent,
    CalendarSptr calendar) {
  auto tabs = std::make_unique<Wt::WTabWidget>();
  tabs->addTab(
      std::make_unique<CalendarSettingsView>(calendar),
      "Создать");
  tabs->addTab(
      std::make_unique<CalendarExportTemplate>(calendar),
      "Экспортировать");
  ShowInternal(parent, std::move(tabs));
}

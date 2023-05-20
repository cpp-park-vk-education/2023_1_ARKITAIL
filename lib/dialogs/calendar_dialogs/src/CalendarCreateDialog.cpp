#include "CalendarCreateDialog.hpp"

#include <memory>

#include <Wt/WDialog.h>
#include <Wt/WObject.h>
#include <Wt/WTabWidget.h>

#include "CalendarDialog.hpp"
#include "CalendarSettingsView.hpp"
#include "CalendarImportView.hpp"

void CreateCalendarDialog::Show(Wt::WObject* parent) {
  auto tabs = std::make_unique<Wt::WTabWidget>();
  tabs->addTab(
      std::make_unique<CalendarSettingsView>(),
      "Создать");
  tabs->addTab(
      std::make_unique<CalendarImportView>(),
      "Импортировать");
  ShowInternal(parent, std::move(tabs));
}

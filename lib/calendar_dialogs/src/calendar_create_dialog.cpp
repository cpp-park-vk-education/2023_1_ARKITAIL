#include "calendar_create_dialog.hpp"

#include <memory>

#include <Wt/WDialog.h>
#include <Wt/WObject.h>
#include <Wt/WTabWidget.h>

#include "calendar_dialog.hpp"
#include "calendar_settings_view.hpp"
#include "calendar_import_view.hpp"

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

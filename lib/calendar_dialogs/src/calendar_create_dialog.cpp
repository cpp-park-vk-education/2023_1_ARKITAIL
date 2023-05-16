#include "calendar_create_dialog.hpp"

#include <memory>

#include <Wt/WDialog.h>
#include <Wt/WObject.h>
#include <Wt/WTabWidget.h>

#include "calendar_settings_view.hpp"
#include "calendar_import_view.hpp"

void CreateCalendarDialog::Show(Wt::WObject* parent) {
  auto dialog = parent->addChild(std::make_unique<Wt::WDialog>());

  dialog->setWindowTitle("Календарь");
  dialog->setMovable(false);
  dialog->setClosable(true);
  dialog->setMinimumSize(500, 600);

  auto tab = dialog->contents()->addWidget(std::make_unique<Wt::WTabWidget>());
  tab->addTab(std::make_unique<CalendarSettingsView>(), "Создать");
  tab->addTab(std::make_unique<CalendarImportView>(), "Импортировать");

  dialog->finished().connect([=]{
    parent->removeChild(dialog);
  });

  dialog->show();
}

#include "calendar_edit_dialog.hpp"

#include <memory>

#include <Wt/WDialog.h>
#include <Wt/WObject.h>
#include <Wt/WTabWidget.h>

#include "calendar.hpp"
#include "calendar_settings_view.hpp"
#include "calendar_export_view.hpp"

void EditCalendarDialog::Show(
    Wt::WObject* parent, std::shared_ptr<Calendar> calendar) {
  auto dialog = parent->addChild(std::make_unique<Wt::WDialog>());

  dialog->setWindowTitle("Календарь");
  dialog->setMovable(false);
  dialog->setClosable(true);
  dialog->setMinimumSize(500, 600);

  auto tab = dialog->contents()->addWidget(std::make_unique<Wt::WTabWidget>());
  tab->addTab(std::make_unique<CalendarSettingsView>(calendar), "Создать");
  tab->addTab(std::make_unique<CalendarExportView>(calendar), "Экспортировать");

  dialog->finished().connect([=]{
    parent->removeChild(dialog);
  });

  dialog->show();
}

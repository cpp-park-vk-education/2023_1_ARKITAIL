#include "EditCalendarDialog.hpp"

#include <Wt/WTabWidget.h>

#include "Calendar.hpp"
#include "CalendarExportTemplate.hpp"
#include "EditCalendarView.hpp"
#include "IManagers.hpp"
#include "SessionScopeMap.hpp"

namespace dialog {
enum EditCalendarTabIndex {
  kSettings = 0,
  kExport = 1,
};

EditCalendarDialog::EditCalendarDialog(CalendarSptr calendar)
    : Wt::WDialog("Календарь") {
  rejectWhenEscapePressed();
  setClosable(true);
  setMinimumSize(500, 600);
  setMovable(false);

  auto tabs = std::make_unique<Wt::WTabWidget>();
  tabs->addTab(std::make_unique<EditCalendarView>(calendar), "Настройки");
  tabs->addTab(std::make_unique<CalendarExportTemplate>(calendar), "Экспорт");
  tabs_ = tabs.get();
  contents()->addWidget(std::move(tabs));

  Wt::WPushButton* submit = footer()->addNew<Wt::WPushButton>("OK");
  submit->clicked().connect(this, &EditCalendarDialog::ChooseHandler);
}

void EditCalendarDialog::ChooseHandler() {
  switch (tabs_->currentIndex()) {
    case EditCalendarTabIndex::kSettings: {
      HandleSettings();
      break;
    }
    case EditCalendarTabIndex::kExport: {
      break;
    }
    default: {
      Wt::log("Undefined EditCalendarDialog tab index");
    }
  }
}

void EditCalendarDialog::HandleSettings() {
  EditCalendarView* settings = dynamic_cast<EditCalendarView*>(
      tabs_->currentWidget());

  if (!settings) {
    Wt::log("Dynamic casting Wt::WWidget* to EditCalendarView* failed");
    return;
  }

  CalendarModel* model = settings->model().get();
  settings->updateModel(model);

  if (model->validate()) {
    model->UpdateCalendar();

    IManagers* managers = SessionScopeMap::instance().get()->managers();
    managers->calendar_manager()->update(model->calendar());
    calendar_updated_.emit(model->calendar());
  }

  settings->updateView(model);
}
} // namespace dialog

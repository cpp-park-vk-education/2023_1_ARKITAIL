#include "EditCalendarDialog.hpp"

#include <Wt/WTabWidget.h>

#include "Calendar.hpp"
#include "CalendarExportTemplate.hpp"
#include "CalendarView.hpp"
#include "IManagers.hpp"
#include "SessionScopeMap.hpp"

namespace dialog {
enum EditCalendarTabIndex {
  kSettings = 0,
  kExport = 1,
};

EditCalendarDialog::EditCalendarDialog(CalendarSptr calendar)
    : Wt::WDialog("Календарь") {
  setClosable(true);
  setWidth(600);
  setHeight(600);
  setMovable(false);

  auto tabs = std::make_unique<Wt::WTabWidget>();
  tabs->addTab(std::make_unique<CalendarView>(calendar), "Настройки");
  tabs->addTab(std::make_unique<CalendarExportTemplate>(calendar), "Экспорт");
  tabs_ = tabs.get();
  contents()->addWidget(std::move(tabs));

  Wt::WPushButton* submit = footer()->addNew<Wt::WPushButton>("OK");
  submit->addStyleClass("btn btn-success");
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
  CalendarView* settings = dynamic_cast<CalendarView*>(
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

    auto validation_success = std::make_unique<Wt::WTemplate>(
        Wt::WString::tr("validation-success"));
    validation_success->bindString("text", "Календарь успешно изменён");
    settings->bindWidget("validation-status", std::move(validation_success));
  } else {
    settings->bindEmpty("validation-status");
  }

  settings->updateView(model);
}

Wt::Signal<CalendarSptr>& EditCalendarDialog::calendar_updated() {
  return calendar_updated_;
}
} // namespace dialog

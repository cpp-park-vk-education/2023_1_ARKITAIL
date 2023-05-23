#include "CreateCalendarDialog.hpp"

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <Wt/WDialog.h>
#include <Wt/WLogger.h>
#include <Wt/WPushButton.h>
#include <Wt/WTabWidget.h>

#include "Calendar.hpp"
#include "CalendarConverter.hpp"
#include "CalendarImportTemplate.hpp"
#include "CreateCalendarModel.hpp"
#include "CreateCalendarView.hpp"
#include "IManagers.hpp"
#include "IstreamCharacterReader.hpp"
#include "SessionScopeMap.hpp"

namespace dialog {
enum CreateCalendarTabIndex {
  kSettings = 0,
  kImport = 1,
};

CreateCalendarDialog::CreateCalendarDialog()
    : Wt::WDialog("Календарь") {
  rejectWhenEscapePressed();
  setClosable(true);
  setMinimumSize(500, 600);
  setMovable(false);

  auto tabs = std::make_unique<Wt::WTabWidget>();
  tabs->addTab(std::make_unique<CreateCalendarView>(), "Создать");
  tabs->addTab(std::make_unique<CalendarImportTemplate>(), "Импорт");
  tabs_ = tabs.get();
  contents()->addWidget(std::move(tabs));

  Wt::WPushButton* submit = footer()->addNew<Wt::WPushButton>("OK");
  submit->clicked().connect(this, &CreateCalendarDialog::ChooseHandler);
}

void CreateCalendarDialog::ChooseHandler() {
  switch (tabs_->currentIndex()) {
    case CreateCalendarTabIndex::kSettings: {
      HandleSettings();
      break;
    }
    case CreateCalendarTabIndex::kImport: {
      HandleImport();
      break;
    }
    default: {
      Wt::log("Undefined CreateCalendarDialog tab index");
    }
  }
}

void CreateCalendarDialog::HandleSettings() {
  CreateCalendarView* settings = dynamic_cast<CreateCalendarView*>(
      tabs_->currentWidget());

  if (!settings) {
    Wt::log("Dynamic casting Wt::WWidget* to CreateCalendarView* failed");
    return;
  }

  CalendarModel* model = settings->model().get();
  settings->updateModel(model);

  if (model->validate()) {
    model->UpdateCalendar();

    IManagers* managers = SessionScopeMap::instance().get()->managers();
    size_t calendar_id = managers->calendar_manager()->add(model->calendar());
    calendar_created_.emit(managers->calendar_manager()->get(calendar_id));

    model->reset();
    model->set_calendar(nullptr);
    Wt::log("Calendar created");
  }

  settings->updateView(model);
}

void CreateCalendarDialog::HandleImport() {
  CalendarImportTemplate* _import = dynamic_cast<CalendarImportTemplate*>(
      tabs_->currentWidget());

  if (!_import) {
    Wt::log("Dynamic casting Wt::WWidget* to CalendarImportTemplate* failed");
    return;
  }

  std::ifstream file(_import->import_icalendar()->spoolFileName());
  std::vector<size_t> calendars_id
    = CalendarConverter::IcalendarToCalendars(
        std::make_unique<parsing::IstreamCharacterReader>(file.rdbuf()));

  if (calendars_id.empty()) {
    Wt::log("iCalendar conversion failed");
    return;
  }

  IManagers* managers = SessionScopeMap::instance().get()->managers();
  for (size_t calendar_id : calendars_id) {
    calendar_created_.emit(managers->calendar_manager()->get(calendar_id));
  }

  Wt::log("Calendar imported");
}

Wt::Signal<CalendarSptr>& CreateCalendarDialog::calendar_created() {
  return calendar_created_;
}
} // namespace dialog

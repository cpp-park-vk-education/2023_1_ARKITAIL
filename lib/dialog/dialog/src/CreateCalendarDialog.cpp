#include "CreateCalendarDialog.hpp"

#include <Wt/WString.h>
#include <Wt/WTemplate.h>
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
#include "IstreamReader.hpp"
#include "SessionScopeMap.hpp"

namespace dialog {
enum CreateCalendarTabIndex {
  kSettings = 0,
  kImport = 1,
};

CreateCalendarDialog::CreateCalendarDialog()
    : Wt::WDialog("Календарь") {
  setClosable(true);
  setMinimumSize(500, 600);
  setMovable(false);

  auto tabs = std::make_unique<Wt::WTabWidget>();
  tabs->addTab(std::make_unique<CreateCalendarView>(), "Создать");
  tabs->addTab(std::make_unique<CalendarImportTemplate>(), "Импорт");
  tabs_ = tabs.get();
  contents()->addWidget(std::move(tabs));

  Wt::WPushButton* submit = footer()->addNew<Wt::WPushButton>("OK");
  submit->addStyleClass("btn btn-success");
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

    auto validation_success = std::make_unique<Wt::WTemplate>(
        Wt::WString::tr("validation-success"));
    validation_success->bindString("text", "Календарь успешно сохранён");
    settings->bindWidget("validation-status", std::move(validation_success));
  } else {
    settings->bindEmpty("validation-status");
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

  std::ifstream source(_import->import_icalendar()->spoolFileName());
  if (!source) {
    Wt::log("exited");
    return;
  }

  std::vector<CalendarSptr> calendars
    = converter::CalendarConverter::IcalendarToCalendars(
        std::make_unique<std::ifstream>(std::move(source)));

  if (calendars.empty()) {
    auto validation_failed = std::make_unique<Wt::WTemplate>(
        Wt::WString::tr("validation-failed"));
    validation_failed->bindString("text", "Не удалось разобрать формат");
    _import->bindWidget("validation-status", std::move(validation_failed));
  } else {
    auto validation_success = std::make_unique<Wt::WTemplate>(
        Wt::WString::tr("validation-success"));
    validation_success->bindString("text", "Календарь успешно сохранён");
    _import->bindWidget("validation-status", std::move(validation_success));
  }
}

Wt::Signal<CalendarSptr>& CreateCalendarDialog::calendar_created() {
  return calendar_created_;
}
} // namespace dialog

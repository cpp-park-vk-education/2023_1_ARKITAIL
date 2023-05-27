#include "CreateCalendarDialog.hpp"

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <Wt/WDialog.h>
#include <Wt/WLogger.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WTabWidget.h>
#include <Wt/WTemplate.h>

#include "Calendar.hpp"
#include "CalendarConverter.hpp"
#include "CalendarImportTemplate.hpp"
#include "CalendarModel.hpp"
#include "CalendarView.hpp"
#include "IManagers.hpp"
#include "ITreeNode.hpp"
#include "IstreamReader.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"

namespace dialog {
enum CreateCalendarTabIndex {
  kSettings = 0,
  kImport = 1,
};

CreateCalendarDialog::CreateCalendarDialog(ITreeNode* node)
    : Wt::WDialog("Календарь"),
      node_(node) {
  setClosable(true);
  setMinimumSize(500, 600);
  setMovable(false);

  auto tabs = std::make_unique<Wt::WTabWidget>();
  tabs->addTab(std::make_unique<CalendarView>(), "Создать");
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
  CalendarView* view = dynamic_cast<CalendarView*>(tabs_->currentWidget());

  if (!view) {
    Wt::log("Dynamic casting Wt::WWidget* to CreateCalendarView* failed");
    return;
  }

  CalendarModel* model = view->model().get();
  view->updateModel(model);

  if (model->validate()) {
    model->UpdateCalendar();

    IManagers* managers = SessionScopeMap::instance().get()->managers();
    // будет заменено на то, что ниже
    size_t calendar_id = managers->calendar_manager()->add(model->calendar(), 0);
    // size_t calendar_id = managers->calendar_manager()->add(
    //     model->calendar(),
    //     node_->getNode().resource_id);
    CalendarSptr created_calendar
        = managers->calendar_manager()->get(calendar_id);
    node_created_.emit(
        managers->node_manager()->get(created_calendar->node_id));

    model->reset();
    model->set_calendar(nullptr);

    auto validation_success = std::make_unique<Wt::WTemplate>(
        Wt::WString::tr("validation-success"));
    validation_success->bindString("text", "Календарь успешно создан");
    view->bindWidget("validation-status", std::move(validation_success));
  } else {
    view->bindEmpty("validation-status");
  }

  view->updateView(model);
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
    return;
  }

  // предполагаем, что один календарь
  
  for (CalendarSptr calendar : calendars) {
    IManagers* managers = SessionScopeMap::instance().get()->managers();
    // будет заменено на то, что ниже
    size_t calendar_id = managers->calendar_manager()->add(calendar, 0);
    // size_t calendar_id = managers->calendar_manager()->add(
    //     calendar,
    //     node_->getNode().resource_id);
    CalendarSptr created_calendar
        = managers->calendar_manager()->get(calendar_id);
    node_created_.emit(
        managers->node_manager()->get(created_calendar->node_id));
  }

  auto validation_success = std::make_unique<Wt::WTemplate>(
      Wt::WString::tr("validation-success"));
  validation_success->bindString("text", "Календарь успешно импортирован");
  _import->bindWidget("validation-status", std::move(validation_success));
}

Wt::Signal<Node>& CreateCalendarDialog::node_created() {
  return node_created_;
}
} // namespace dialog

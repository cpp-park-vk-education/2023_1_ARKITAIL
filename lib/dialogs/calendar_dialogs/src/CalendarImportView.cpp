#include "CalendarImportView.hpp"

#include <fstream>
#include <memory>

#include <Wt/WFileUpload.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WTemplateFormView.h>

#include "Calendar.hpp"
#include "CalendarImportModel.hpp"
#include "CalendarConverter.hpp"
#include "FileCharacterReader.hpp"
#include "ICharacterReader.hpp"

CalendarImportView::CalendarImportView() {
  model_ = std::make_shared<CalendarImportModel>();

  setTemplateText(Wt::WString::tr("calendar-import"));

  addFunction("id", &Wt::WTemplate::Functions::id);

  auto import_iCalendar = std::make_unique<Wt::WFileUpload>();
  import_iCalendar_ = import_iCalendar.get();
  import_iCalendar_->changed().connect([=] {
    if (import_iCalendar_->canUpload()) {
      import_iCalendar_->upload();
    }
  });

  setFormWidget(
      CalendarImportModel::kImportIcalendar, std::move(import_iCalendar));

  auto button = bindWidget(
      "submit-button", std::make_unique<Wt::WPushButton>("OK"));
  bindString("submit-info", Wt::WString());
  button->addStyleClass("btn btn-success");
  button->clicked().connect(this, &CalendarImportView::HandleInput);
  
  updateView(model_.get());
}

void CalendarImportView::HandleInput() {
  updateModel(model_.get());

  std::ifstream icalendar(import_iCalendar_->spoolFileName());
  CalendarConverter converter;
  std::vector<CalendarSptr> calendars = converter.IcalendarToCalendar(
      std::make_unique<FileCharacterReader>(std::move(icalendar)));

  for (CalendarSptr calendar : calendars) {
    calendar_created_.emit(calendar);
    // Раскомментировать при слиянии:
    // calendar_manager.add(model_->GetData());
  }

  if (!calendars.empty()) {
    bindString("submit-info", "Успешно сохранено!");
  } else {
    bindString("submit-info", "Не удалось разобрать формат!");
  }
  
  updateView(model_.get());
}

Wt::Signal<std::shared_ptr<Calendar>>& CalendarImportView::calendar_created() {
  return calendar_created_;
}
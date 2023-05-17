#include "calendar_import_view.hpp"

#include <fstream>
#include <memory>

#include <Wt/WFileUpload.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WTemplateFormView.h>

#include "calendar.hpp"
#include "calendar_import_model.hpp"
#include "calendar_converter.hpp"
#include "file_char_reader.hpp"
#include "i_char_reader.hpp"

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
      CalendarImportModel::kImportiCalendarField, std::move(import_iCalendar));

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
      std::make_unique<FileCharReader>(std::move(icalendar)));

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

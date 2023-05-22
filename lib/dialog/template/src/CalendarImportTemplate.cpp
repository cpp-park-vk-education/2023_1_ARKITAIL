#include "CalendarImportTemplate.hpp"

#include <fstream>
#include <memory>

#include <Wt/WFileUpload.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WTemplateFormView.h>

#include "ICharacterReader.hpp"

#include "Calendar.hpp"
#include "CalendarConverter.hpp"
#include "IstreamCharacterReader.hpp"
#include "SessionScopeMap.hpp"

namespace dialog {
CalendarImportTemplate::CalendarImportTemplate()
    : Wt::WTemplate(Wt::WString::tr("calendar-import")) {

  addFunction("id", &Wt::WTemplate::Functions::id);

  auto import_icalendar = std::make_unique<Wt::WFileUpload>();
  import_icalendar_ = import_icalendar.get();
  import_icalendar_->changed().connect([=] {
    if (import_icalendar_->canUpload()) {
      import_icalendar_->upload();
    }
  });

  bindWidget("import-icalendar", std::move(import_icalendar));

  auto button = bindWidget(
      "submit-button",
      std::make_unique<Wt::WPushButton>("OK"));
  bindString("submit-info", std::string());
  button->addStyleClass("btn btn-success");
  button->clicked().connect(this, &CalendarImportTemplate::HandleInput);
}

void CalendarImportTemplate::HandleInput() {
  std::ifstream icalendar(import_icalendar_->spoolFileName());

  // сохранение разобранных календарей и событий в БД происходит в
  // CalendarConverter::IcalendarToCalendars
  std::vector<size_t> calendars_id = CalendarConverter::IcalendarToCalendars(
        std::make_unique<parsing::IstreamCharacterReader>(icalendar.rdbuf()));
  auto calendar_manager
    = SessionScopeMap::instance().get()->managers()->calendar_manager();
  for (size_t calendar_id : calendars_id) {
    // Выпуск сигнала для обновления дерева
    calendar_created_.emit(calendar_manager->get(calendar_id));
  }

  // вектор пустой, если не удалось разобрать файл;
  if (!calendars_id.empty()) {
    bindString("submit-info", "Календарь успешно импортирован");
  } else {
    bindString("submit-info", "Не удалось разобрать формат");
  }
}

Wt::Signal<CalendarSptr>& CalendarImportTemplate::calendar_created() {
  return calendar_created_;
}
} // namespace dialog

#include "CreateCalendarDialog.hpp"

#include <memory>

#include <Wt/WObject.h>
#include <Wt/WTabWidget.h>

#include "CreateCalendarView.hpp"
#include "CalendarImportTemplate.hpp"

namespace dialog {
CreateCalendarDialog::CreateCalendarDialog(Wt::WObject* parent) {
  parent_ = parent;

  auto tabs = std::make_unique<Wt::WTabWidget>();
  tabs->addTab(std::make_unique<CreateCalendarView>(), "Создать");
  tabs->addTab(std::make_unique<CalendarImportTemplate>(), "Импорт");
  contents_ = std::move(tabs);

  title_ = "Календарь";
  min_width_ = 500;
  min_height_ = 500;
}
} // namespace dialog

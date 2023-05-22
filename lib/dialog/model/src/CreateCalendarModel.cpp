#include "CreateCalendarModel.hpp"
#include "CalendarModel.hpp"

#include <Wt/WTime.h>

namespace dialog {
CreateCalendarModel::CreateCalendarModel()
  : CalendarModel(nullptr) {
}

void CreateCalendarModel::UpdateCalendar() {
  calendar_ = std::make_shared<Calendar>();

  calendar_->summary = Wt::asString(value(kSummary)).toUTF8();
  calendar_->description = Wt::asString(value(kDescription)).toUTF8();
  calendar_->visibility = Wt::asString(value(kVisibility)).toUTF8();
  calendar_->color = Wt::asString(value(kColor)).toUTF8();
}

void CreateCalendarModel::SetValues() {
  // цвет по умолчанию
  setValue(kColor, "#f4d03f");
}
} // namespace dialog

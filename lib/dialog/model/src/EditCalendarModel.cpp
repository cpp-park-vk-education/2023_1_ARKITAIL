#include "EditCalendarModel.hpp"

#include "Calendar.hpp"

namespace dialog {
EditCalendarModel::EditCalendarModel(CalendarSptr calendar)
    : CalendarModel(calendar) {
}

void EditCalendarModel::UpdateCalendar() {
  // id, node_id, owner_id остаются теми же
  calendar_->summary = Wt::asString(value(kSummary)).toUTF8();
  calendar_->description = Wt::asString(value(kDescription)).toUTF8();
  calendar_->visibility = Wt::asString(value(kVisibility)).toUTF8();
  calendar_->color = Wt::asString(value(kColor)).toUTF8();
}

void EditCalendarModel::SetValues() {
  setValue(kSummary, calendar_->summary);
  setValue(kDescription, calendar_->description);
  setValue(kVisibility, calendar_->visibility);
  setValue(kColor, calendar_->color);
}
} // namespace dialog

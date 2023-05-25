#include "EditEventModel.hpp"

#include "Event.hpp"

#include <Wt/WTime.h>

namespace dialog {
EditEventModel::EditEventModel(EventSptr event)
    : EventModel(event) {
}

void EditEventModel::UpdateEvent() {
  event_->summary = Wt::asString(value(kSummary)).toUTF8();
  event_->description = Wt::asString(value(kDescription)).toUTF8();
  // TODO(affeeal): разобраться с event->calendars

  event_->start = Wt::WDateTime(
      Wt::cpp17::any_cast<Wt::WDate>(value(kStartDate)),
      Wt::cpp17::any_cast<Wt::WTime>(value(kStartTime)));
  event_->end = Wt::WDateTime(
      Wt::cpp17::any_cast<Wt::WDate>(value(kEndDate)),
      Wt::cpp17::any_cast<Wt::WTime>(value(kEndTime)));

  event_->is_recurrent = Wt::cpp17::any_cast<bool>(value(kIsRecurrent));
  event_->frequency = Wt::asString(value(kFrequency)).toUTF8();
  event_->interval = Wt::cpp17::any_cast<std::size_t>(value(kInterval));
  event_->until = Wt::cpp17::any_cast<Wt::WDate>(value(kEndDate));
}

void EditEventModel::SetValues() {
  setValue(kSummary, event_->summary);
  setValue(kDescription, event_->description);
  // TODO(affeeal): разобраться с event->calendars

  setValue(kStartDate, event_->start.date());
  setValue(kStartTime, event_->start.time());
  setValue(kEndDate, event_->end.date());
  setValue(kEndTime, event_->end.time());

  setValue(kIsRecurrent, event_->is_recurrent);
  setValue(kFrequency, event_->frequency);
  setValue(kInterval, event_->interval);
  setValue(kUntil, event_->until);
}
} // namespace dialog

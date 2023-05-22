#include "CreateEventModel.hpp"
#include "EventModel.hpp"

#include <Wt/WTime.h>

namespace dialog {
CreateEventModel::CreateEventModel()
    : EventModel(nullptr) {
}

void CreateEventModel::UpdateEvent() {
  event_ = std::make_shared<Event>();

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

void CreateEventModel::SetValues() {
  // TODO(affeeal): разобраться с event->calendars
  setValue(kStartDate, Wt::WDate::currentServerDate());
  setValue(kStartTime, Wt::WTime::currentServerTime());
  setValue(kEndDate, Wt::WDate::currentServerDate());
  setValue(kEndTime, Wt::WTime::currentServerTime().addSecs(3600));
  setValue(kIsRecurrent, true);
  setValue(kInterval, 1);
}
} // namespace dialog

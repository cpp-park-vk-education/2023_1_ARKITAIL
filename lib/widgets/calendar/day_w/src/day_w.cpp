#include "day_w.hpp"

#include "event_w.hpp"
#include "time_utils.hpp"

DayW::DayW() {
    table_->setHeaderCount(1, Wt::Orientation::Vertical);
}

void DayW::update(Wt::WDate selected_date_) {
    table_->clear();
    makeHeaderTime();
    table_->insertColumn(1);
    table_->insertRow(0);
    for (int i = 0; i < TimeInterval::HOURS_PER_DAY; i++) {
        table_->elementAt(i, 1)->addStyleClass("w-100");
    }

    std::vector<EventW> events = {EventW(0, "Event0 цыцы ыцы", Wt::WColor(200, 50, 50, 50),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 11), Wt::WTime(12, 45)),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 18), Wt::WTime(14, 0))),
                                  EventW(1, "Event1", Wt::WColor(50, 20, 220, 50),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 15), Wt::WTime(12, 45)),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 19), Wt::WTime(14, 0))),
                                  EventW(2, "Event2", Wt::WColor(250, 20, 220, 50),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 20), Wt::WTime(12, 45)),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 30), Wt::WTime(14, 0))),
                                  EventW(3, "Event3", Wt::WColor(25, 20, 220, 50),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 15), Wt::WTime(12, 45)),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 15), Wt::WTime(14, 0))),
                                  EventW(4, "Event4", Wt::WColor(25, 200, 220, 50),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 15), Wt::WTime(0, 0)),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 15), Wt::WTime(23, 59)))};
    for (auto&& event : events) {
        event.makeDayEventWidget(table_);
    }
}

#include "day_w.hpp"

#include "EventW.hpp"
#include "time_utils.hpp"
#include "SessionScopeMap.hpp"

DayW::DayW() {
    table_->setHeaderCount(1, Wt::Orientation::Vertical);
}

void DayW::update(Wt::WDate begin_date, std::vector<Event> events) {
    table_->clear();
    makeHeaderTime();
    table_->insertColumn(1);
    table_->insertRow(0);
    for (int i = 0; i < TimeInterval::HOURS_PER_DAY; i++) {
        table_->elementAt(i, 1)->addStyleClass("w-100");
    }

    std::vector<EventW> events_w;

    auto calendar_mgr = SessionScopeMap::instance().get()->managers()->calendar_manager();

    for (auto event : events) {
        auto color = Wt::WColor(calendar_mgr->get(event.calendar_id)->color);
        events_w.push_back(EventW(event.id, event.summary, color, event.start, event.end));
    }

    for (auto&& event : events_w) {
        event.makeDayEventWidget(table_);
    }
}

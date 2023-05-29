#include "month_w.hpp"

#include <Wt/WBreak.h>

#include "EventW.hpp"
#include "SessionScopeMap.hpp"
#include "time_utils.hpp"

MonthW::MonthW() {
    table_->setHeaderCount(1);
    table_->setHeaderCount(1, Wt::Orientation::Vertical);
    table_->addStyleClass("week");
}

void MonthW::update(Wt::WDate begin_date, std::vector<Event> events) {
    auto begin_week_day = begin_date;
    table_->clear();

    for (size_t i = 1; i < 6; ++i) {
        table_->elementAt(i, 0)->addNew<Wt::WBreak>();
        table_->elementAt(i, 0)->addStyleClass("py-4");
    }

    for (int i{1}; auto&& weekday : {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"}) {
        table_->elementAt(0, i++)->addNew<Wt::WText>(weekday)->addStyleClass("mx-auto");
        begin_week_day = begin_week_day.addDays(1);
    }
    auto day = begin_date;
    auto today = Wt::WDate(std::chrono::system_clock::now());
    for (auto pos = 0; pos < 5 * TimeInterval::DAYS_IN_WEEK; day = day.addDays(1)) {
        auto text = table_->elementAt(1 + (pos++) / TimeInterval::DAYS_IN_WEEK, (day.dayOfWeek()))
                        ->addNew<Wt::WText>(std::to_string(day.day()));
        text->addStyleClass("mx-auto d-block px-auto py-1 text-center");
        if (day == today) {
            text->addStyleClass(" today-color");
        }
    }

    std::vector<EventW> events_w;

    auto calendar_mgr = SessionScopeMap::instance().get()->managers()->calendar_manager();

    for (auto event : events) {
        auto color = Wt::WColor(calendar_mgr->get(event.calendar_id)->color);
        events_w.push_back(EventW(event.id, event.summary, color, event.start, event.end));
    }

    for (auto&& event : events_w) {
        event.makeMonthEventWidget(table_, begin_date);
    }
}

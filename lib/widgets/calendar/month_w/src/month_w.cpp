#include "month_w.hpp"

#include "Wt/WBreak.h"
#include "event_w.hpp"
#include "time_utils.hpp"

MonthW::MonthW() {
    table_->setHeaderCount(1);
    table_->setHeaderCount(1, Wt::Orientation::Vertical);
    table_->addStyleClass("week");
}

void MonthW::update(Wt::WDate selected_date) {
    auto begin_week_day = selected_date;
    table_->clear();

    for (size_t i = 1; i < 6; ++i) {
        table_->elementAt(i, 0)->addNew<Wt::WText>("ㅤ");
        table_->elementAt(i, 0)->addStyleClass("py-4");
    }

    for (int i{1}; auto&& weekday : {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"}) {
        table_->elementAt(0, i++)->addNew<Wt::WText>(weekday);
        begin_week_day = begin_week_day.addDays(1);
    }

    for (int day = selected_date.dayOfWeek();
         day < selected_date.daysTo(selected_date.addMonths(1)); day++) {
        table_
            ->elementAt(1 + (day) / TimeInterval::DAYS_IN_WEEK,
                        (day) % TimeInterval::DAYS_IN_WEEK + 1)
            ->addNew<Wt::WText>(std::to_string(day - selected_date.dayOfWeek()));
    }

    std::vector<EventW> events = {EventW(0, "Event0 цыцы ыцы", Wt::WColor(200, 50, 50, 50),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 11), Wt::WTime(12, 45)),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 18), Wt::WTime(14, 0))),
                                  EventW(1, "Event1", Wt::WColor(50, 20, 220, 50),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 15), Wt::WTime(12, 45)),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 19), Wt::WTime(14, 0))),
                                  EventW(2, "Event2", Wt::WColor(250, 20, 220, 50),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 10), Wt::WTime(12, 45)),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 30), Wt::WTime(14, 0))),
                                  EventW(3, "Event3", Wt::WColor(25, 20, 220, 50),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 15), Wt::WTime(12, 45)),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 15), Wt::WTime(14, 0))),
                                  EventW(4, "Event4", Wt::WColor(25, 200, 220, 50),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 15), Wt::WTime(0, 0)),
                                         Wt::WDateTime(Wt::WDate(2023, 5, 15), Wt::WTime(23, 59)))};
    for (auto&& event : events) {
        event.makeMonthEventWidget(table_, selected_date);
    }
}

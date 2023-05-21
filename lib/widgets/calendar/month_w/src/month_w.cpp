#include "month_w.hpp"

#include "Wt/WBreak.h"
#include "event_w.hpp"

MonthW::MonthW() {
    table_->setHeaderCount(1);
    table_->setHeaderCount(1, Wt::Orientation::Vertical);
    table_->addStyleClass("week");
}

void MonthW::update(Wt::WDate selected_date) {
    auto begin_week_day = std::make_unique<Wt::WDate>(selected_date);
    auto first_day = Wt::WDate(selected_date.year(), selected_date.month(), 1);
    table_->clear();

    for (unsigned i = 1; i < 6; ++i) {
        table_->elementAt(i, 0)->addNew<Wt::WText>("ㅤ");
        table_->elementAt(i, 0)->addStyleClass("py-4");
    }

    for (int i{1}; auto&& weekday : {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"}) {
        table_->elementAt(0, i++)->addNew<Wt::WText>(weekday);
        begin_week_day = std::make_unique<Wt::WDate>(begin_week_day->addDays(1));
    }
    std::cout << first_day.toString("dd MMMM yyyy");

    for (int day = 1 + first_day.dayOfWeek();
         day < selected_date.daysTo(selected_date.addMonths(1).addDays(first_day.dayOfWeek()));
         day++) {
        table_->elementAt(1 + (day) / 7, (day) % 7 + 1)
            ->addNew<Wt::WText>(std::to_string(day - first_day.dayOfWeek()));
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

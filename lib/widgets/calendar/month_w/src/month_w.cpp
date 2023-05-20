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
    table_->clear();

    for (unsigned i = 1; i < 6; ++i) {
        table_->elementAt(i, 0)->addNew<Wt::WText>("ㅤ");
        table_->elementAt(i, 0)->addStyleClass("py-4");
    }

    for (int i{1}; auto&& weekday : {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"}) {
        table_->elementAt(0, i++)->addNew<Wt::WText>(weekday);
        begin_week_day = std::make_unique<Wt::WDate>(begin_week_day->addDays(1));
    }

    for (int day = 1; day < selected_date.daysTo(selected_date.addMonths(1)); day++) {
        table_->elementAt(1 + (day) / 7, (day) % 7 + 1)->addNew<Wt::WText>(std::to_string(day));
    }
}

#include "month_w.hpp"

#include "event_w.hpp"

MonthW::MonthW() {
    table_->setHeaderCount(1);
    table_->addStyleClass("week");

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 5; j++) {
            table_->elementAt(j, i)->setWidth(Wt::WLength("14%"));
        }
    }
}

void MonthW::update(Wt::WDate selected_date) {
    auto begin_week_day = std::make_unique<Wt::WDate>(selected_date);
    table_->clear();

    for (int i{0}; auto &&weekday : {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"}) {
        table_->elementAt(0, i++)->addNew<Wt::WText>(weekday);
        begin_week_day = std::make_unique<Wt::WDate>(begin_week_day->addDays(1));
    }

    for (int day = 0; day < selected_date.daysTo(selected_date.addMonths(1)); day++) {
        table_->elementAt(1 + (day) / 7, (day) % 7)->addNew<Wt::WText>(std::to_string(day));
    }
}

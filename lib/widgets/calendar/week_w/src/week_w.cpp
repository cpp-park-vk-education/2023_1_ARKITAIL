#include "week_w.hpp"

#include <Wt/WColor.h>
#include <Wt/WDate.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WTime.h>

#include <calendar_body_w.hpp>
#include <event_w.hpp>
#include <memory>
#include <vector>

WeekW::WeekW() {
    table_->setHeaderCount(1);
    table_->setHeaderCount(1, Wt::Orientation::Vertical);
    table_->addStyleClass("week");
    update(Wt::WDate(std::chrono::system_clock::now()));
}

void WeekW::update(Wt::WDate selected_date_) {
    auto selected_date = std::make_unique<Wt::WDate>(selected_date_.year(), selected_date_.month(),
                                                     selected_date_.day());
    table_->clear();
    makeHeaderTime();
    table_->insertRow(0);

    selected_date =
        std::make_unique<Wt::WDate>(selected_date->addDays(-selected_date->dayOfWeek() + 1));
    auto begin_week_day = std::make_unique<Wt::WDate>(selected_date->addDays(0));
    activateToday(selected_date.get(), begin_week_day->day(), 0);
    // Заголовок недели
    for (int i{1}; auto&& weekday : {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"}) {
        table_->elementAt(0, i)->addNew<Wt::WText>(weekday);
        table_->elementAt(0, i++)->addNew<Wt::WText>(", " + std::to_string(begin_week_day->day()));
        begin_week_day = std::make_unique<Wt::WDate>(begin_week_day->addDays(1));
    }

    table_->insertRow(1);
    //  запрос событий нужного промежутка (range, selected_date)
    //  !!!они будут частично или полностью принадлежать промежутку

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
        event.makeWeekEventWidget(table_, *(selected_date));
    }
}

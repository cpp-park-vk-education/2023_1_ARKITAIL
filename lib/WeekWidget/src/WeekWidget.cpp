#include "WeekWidget.hpp"

#include <Wt/WColor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WTime.h>

#include <CalendarBodyWidget.hpp>
#include <EventWidget.hpp>
#include <memory>
#include <vector>

WeekWidget::WeekWidget() { updateCalendar(std::make_unique<Wt::WDate>(std::chrono::system_clock::now())); }

void WeekWidget::updateCalendar(std::unique_ptr<Wt::WDate> selected_date) {
    table_->clear();
    //  запрос событий нужного промежутка (range, selected_date)
    //  !!!они будут частично или полностью принадлежать промежутку

    std::vector<EventWidget> events = {
        EventWidget(0, "Event0 цыцы ыцыцыцыцы вувув", Wt::WColor(200, 50, 50, 50),
                    Wt::WDateTime(Wt::WDate(2023, 4, 20), Wt::WTime(12, 45)),
                    Wt::WDateTime(Wt::WDate(2023, 4, 20), Wt::WTime(14, 0))),
        EventWidget(1, "Event1", Wt::WColor(50, 20, 220, 50), Wt::WDateTime(Wt::WDate(2023, 4, 20), Wt::WTime(12, 45)),
                    Wt::WDateTime(Wt::WDate(2023, 4, 26), Wt::WTime(14, 0))),
        EventWidget(2, "Event2", Wt::WColor(250, 20, 220, 50), Wt::WDateTime(Wt::WDate(2023, 4, 25), Wt::WTime(12, 45)),
                    Wt::WDateTime(Wt::WDate(2023, 4, 30), Wt::WTime(14, 0)))};

    table_->setHeaderCount(1);
    table_->setHeaderCount(1, Wt::Orientation::Vertical);
    table_->addStyleClass("week");
    makeHeaderTime();

    selected_date = std::make_unique<Wt::WDate>(selected_date->addDays(-selected_date->dayOfWeek() + 1));
    auto begin_week_day = std::make_unique<Wt::WDate>(selected_date->addDays(0));

    for (int i{1}; auto &&weekday : {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"}) {
        table_->elementAt(0, i)->addNew<Wt::WText>(weekday);
        table_->elementAt(0, i++)->addNew<Wt::WText>(", " + std::to_string(begin_week_day->day()));
        begin_week_day = std::make_unique<Wt::WDate>(begin_week_day->addDays(1));
    }

    table_->insertRow(1);
    for (auto &&event : events) {
        event.makeEventWidget(table_, *(selected_date));
    }

    activateToday(std::move(selected_date), begin_week_day->day(), 0);
}

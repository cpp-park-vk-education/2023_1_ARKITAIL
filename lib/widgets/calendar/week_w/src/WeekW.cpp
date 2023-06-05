#include "WeekW.hpp"

#include <Wt/WColor.h>
#include <Wt/WDate.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WTime.h>

#include <memory>
#include <vector>

#include "CalendarBodyW.hpp"
#include "Event.hpp"
#include "EventW.hpp"
#include "SessionScopeMap.hpp"

WeekW::WeekW() {
    table_->setHeaderCount(1);
    table_->setHeaderCount(1, Wt::Orientation::Vertical);
    table_->addStyleClass("week");
    Wt::WDate now_date = Wt::WDate(std::chrono::system_clock::now());
    update(now_date.addDays(1 - now_date.dayOfWeek()), std::vector<Event>());
}

void WeekW::update(Wt::WDate begin_date, std::vector<Event> events) {
    table_->clear();
    makeHeaderTime();
    table_->insertRow(0);

    auto begin_week_day = begin_date;
    // Вектор названий вынести в константы
    // Исправить range-based for на обычный

    // Заголовок недели
    for (int i{1}; auto weekday : {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"}) {
        table_->elementAt(0, i)->addNew<Wt::WText>(weekday);
        table_->elementAt(0, i++)->addNew<Wt::WText>(", " + std::to_string(begin_week_day.day()));
        begin_week_day = begin_week_day.addDays(1);
    }
    
    activateToday(begin_date);
    table_->insertRow(1);

    std::vector<EventW> events_w;

    auto calendar_mgr = SessionScopeMap::instance().get()->managers()->calendar_manager();

    for (auto event : events) {
        auto color = Wt::WColor(calendar_mgr->get(event.calendar_id)->color);
        events_w.push_back(EventW(event.id, event.summary, color, event.start, event.end));
    }

    for (auto event : events_w) {
        event.makeWeekEventWidget(table_, begin_date);
    }
}

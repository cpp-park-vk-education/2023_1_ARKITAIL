#include "calendar_body_w.hpp"

#include <Wt/WContainerWidget.h>
#include <Wt/WString.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>

#include <memory>

#include "time_utils.hpp"

CalendarBodyW::CalendarBodyW() {
    table_ = addWidget(std::make_unique<Wt::WTable>());
    table_->setWidth(Wt::WLength("100%"));
    table_->addStyleClass("table table-bordered table-sm d-block w-100");
}

void CalendarBodyW::makeHeaderTime() {
    for (size_t hour = 0; hour < TimeInterval::HOURS_PER_DAY; ++hour) {
        table_->elementAt(hour, 0)->addNew<Wt::WText>(createTime(hour));
    }
}

void CalendarBodyW::updateCalendar(Wt::WDate selected_date) {
    if (isVisible()) {
        update(selected_date);
    }
}

void CalendarBodyW::activateToday(Wt::WDate& selected_date) {
    auto today_day = Wt::WDate(std::chrono::system_clock::now());
    if (selected_date.month() == today_day.month() && today_day.day() >= selected_date.day() &&
        today_day.day() < selected_date.day() + TimeInterval::DAYS_IN_WEEK) {
        table_->elementAt(0, today_day.dayOfWeek())->addStyleClass("table-success");
    }
}

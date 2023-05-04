#include "CalendarBodyW.hpp"

#include <Wt/WContainerWidget.h>
#include <Wt/WString.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>

#include <memory>

CalendarBodyW::CalendarBodyW() {
    auto table = std::make_unique<Wt::WTable>();
    table_ = table.get();
    table_->setWidth(Wt::WLength("100%"));
    table_->addStyleClass("table table-bordered table-sm d-block");
    addWidget(std::move(table));
}

void CalendarBodyW::makeHeaderTime() {
    for (unsigned i = 0; i < 24; ++i) {
        table_->elementAt(i + 1, 0)->addNew<Wt::WText>(Wt::WString(i < 10 ? "0{1}:00" : "{1}:00").arg(i));
    }
}

void CalendarBodyW::activateToday(Wt::WDate* selected_date, int begin_week_day, int shift) {
    auto today_day = std::make_unique<Wt::WDate>(std::chrono::system_clock::now());
    if (selected_date->month() == today_day->month() && today_day->day() >= begin_week_day &&
        today_day->day() <= begin_week_day + 7) {
        table_->elementAt(0, today_day->dayOfWeek() + shift)->addStyleClass("table-success");
    }
}
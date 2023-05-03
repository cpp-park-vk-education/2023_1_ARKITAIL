#include "CalendarWidget.hpp"

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>

#include <memory>

#include "CalendarBodyWidget.hpp"
#include "CalendarHeaderWidget.hpp"
#include "DayWidget.hpp"
#include "MonthWidget.hpp"
#include "WeekWidget.hpp"
#include "utils.hpp"

CalendarWidget::CalendarWidget() {
    // tree_ = addWidget(std::make_unique<>());
    header_ = addWidget(std::make_unique<CalendarHeaderWidget>());
    calendar_ = addWidget(std::make_unique<WeekWidget>());
    void addConnections();
}

void CalendarWidget::addConnections() {
    header_->rangeChanged().connect(calendar_, &CalendarWidget::setCalendarRange);
    // header_->selectedDateChanged().connect(calendar_, &CalendarBodyWidget::updateCalendar);
}

void CalendarWidget::setCalendarRange(Range range) {
    switch (range) {
        case day:
            // calendar_ = addWidget(std::make_unique<DayWidget>());
            break;
        case week:
            calendar_ = addWidget(std::make_unique<WeekWidget>());
            break;
        case month:
            // calendar_ = addWidget(std::make_unique<MonthWidget>());
            break;
    }
}
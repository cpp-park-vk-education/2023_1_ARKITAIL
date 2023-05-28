#include "OtherP.hpp"

#include "CalendarBodyW.hpp"
#include "TreeW.hpp"
#include "WeekW.hpp"
#include "calendar_header_w.hpp"
#include "calendar_w.hpp"
#include "day_w.hpp"
#include "month_w.hpp"

OtherP::OtherP() {
    calendar_ = addWidget(std::make_unique<CalendarW>());
    auto tree = calendar_->addTree(std::make_unique<TreeW>());
    calendar_->addHeader(std::make_unique<CalendarHeaderW>())->addButtons()->addConnections();
    calendar_->addCalendarBodyDay(std::make_unique<DayW>());
    calendar_->addCalendarBodyWeek(std::make_unique<WeekW>());
    calendar_->addCalendarBodyMonth(std::make_unique<MonthW>());
    calendar_->addConnections();
}

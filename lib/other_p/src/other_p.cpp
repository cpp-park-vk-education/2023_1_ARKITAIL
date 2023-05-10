#include "other_p.hpp"

#include "calendar_body_w.hpp"
#include "calendar_header_w.hpp"
#include "calendar_w.hpp"
#include "day_w.hpp"
#include "month_w.hpp"
#include "week_w.hpp"

OtherP::OtherP() {
    calendar_ = addWidget(std::make_unique<CalendarW>());
    calendar_->addHeader(std::make_unique<CalendarHeaderW>());
    calendar_->addCalendarBodyDay(std::make_unique<DayW>());
    calendar_->addCalendarBodyWeek(std::make_unique<WeekW>());
    calendar_->addCalendarBodyMonth(std::make_unique<MonthW>());
    calendar_->addConnections();
    calendar_->setHeaderRange();
}

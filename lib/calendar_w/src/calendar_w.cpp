#include "calendar_w.hpp"

#include <Wt/WApplication.h>
#include <Wt/WBorderLayout.h>
#include <Wt/WContainerWidget.h>

#include <memory>

#include "calendar_body_w.hpp"
#include "calendar_header_w.hpp"
#include "day_w.hpp"
#include "month_w.hpp"
#include "tree_w.hpp"
#include "utils.hpp"
#include "week_w.hpp"

CalendarW::CalendarW() : calendars_(3) {
    auto layout = setLayout(std::make_unique<Wt::WBorderLayout>());
    tree_ = layout->addWidget(std::make_unique<TreeW>(), Wt::LayoutPosition::West);
    calendar_box_ = layout->addWidget(std::make_unique<WContainerWidget>(), Wt::LayoutPosition::Center);
}

void CalendarW::setHeaderRange() { header_->setRange(); }

InterfaceCalendarHeaderW* CalendarW::addHeader(std::unique_ptr<InterfaceCalendarHeaderW> header) {
    return header_ = calendar_box_->addWidget(std::move(header));
}

InterfaceCalendarBodyW* CalendarW::addCalendarBodyDay(std::unique_ptr<InterfaceCalendarBodyW> calendar) {
    calendars_[day] = calendar_box_->addWidget(std::move(calendar));
    calendars_[day]->setHidden(true);
    return calendars_[day];
}

InterfaceCalendarBodyW* CalendarW::addCalendarBodyWeek(std::unique_ptr<InterfaceCalendarBodyW> calendar) {
    range_ = week;
    return calendars_[week] = calendar_box_->addWidget(std::move(calendar));
}

InterfaceCalendarBodyW* CalendarW::addCalendarBodyMonth(std::unique_ptr<InterfaceCalendarBodyW> calendar) {
    calendars_[month] = calendar_box_->addWidget(std::move(calendar));
    calendars_[month]->setHidden(true);
    return calendars_[month];
}

void CalendarW::addConnections() {
    header_->rangeChanged().connect(this, &CalendarW::setCalendarRange);
    header_->selectedDateChanged().connect(calendars_[range_], &InterfaceCalendarBodyW::updateCalendar);
}

void CalendarW::setCalendarRange(Range range) {
    calendars_[range_]->setHidden(true);
    calendars_[range]->setHidden(false);
    range_ = range;
}
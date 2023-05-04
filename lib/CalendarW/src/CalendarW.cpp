#include "CalendarW.hpp"

#include <Wt/WApplication.h>
#include <Wt/WBorderLayout.h>
#include <Wt/WContainerWidget.h>

#include <memory>

#include "CalendarBodyW.hpp"
#include "CalendarHeaderW.hpp"
#include "DayW.hpp"
#include "MonthW.hpp"
#include "TreeW.hpp"
#include "WeekW.hpp"
#include "utils.hpp"

CalendarW::CalendarW() {
    auto layout = setLayout(std::make_unique<Wt::WBorderLayout>());
    tree_ = layout->addWidget(std::make_unique<TreeW>(), Wt::LayoutPosition::West);
    calendar_box_ = layout->addWidget(std::make_unique<WContainerWidget>(), Wt::LayoutPosition::Center);
    header_ = calendar_box_->addWidget(std::make_unique<CalendarHeaderW>());
    calendar_ = calendar_box_->addWidget(std::make_unique<WeekW>());
    addConnections();

    header_->setRange();
}

void CalendarW::addConnections() {
    header_->rangeChanged().connect(this, &CalendarW::setCalendarRange);
    header_->selectedDateChanged().connect(calendar_, &CalendarBodyW::updateCalendar);
}

void CalendarW::setCalendarRange(Range range) {
    // calendar_box_->removeWidget(calendar_);
    switch (range) {
        case day:
            calendar_ = calendar_box_->addWidget(std::make_unique<DayW>());
            break;
        case week:
            calendar_ = calendar_box_->addWidget(std::make_unique<WeekW>());
            break;
        case month:
            calendar_ = calendar_box_->addWidget(std::make_unique<MonthW>());
            break;
    }
}
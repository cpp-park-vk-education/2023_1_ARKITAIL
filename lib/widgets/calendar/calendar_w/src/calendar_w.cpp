#include "calendar_w.hpp"

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>

#include <memory>

#include "calendar_body_w.hpp"
#include "calendar_header_w.hpp"
#include "day_w.hpp"
#include "month_w.hpp"
#include "tree_w.hpp"
#include "week_w.hpp"

CalendarW::CalendarW() :
    calendars_(3) {
    auto layout = setLayout(std::make_unique<Wt::WHBoxLayout>());
    auto tree_panel = layout->addWidget(std::make_unique<Wt::WContainerWidget>());
    tree_panel->setStyleClass("start-0");
    auto tree_panel_layout = tree_panel->setLayout(std::make_unique<Wt::WHBoxLayout>());
    tree_ = tree_panel_layout->addWidget(std::make_unique<TreeW>());
    tree_->setRoot(Node(0, 0, 0, NodeType::ROOT));
    show_tree_button_ =
        tree_panel_layout->addWidget(std::make_unique<Wt::WPushButton>(Wt::WString(">")));
    show_tree_button_->setStyleClass("btn-light rounded-end rounded-0 border-start-0");
    calendar_box_ = layout->addWidget(std::make_unique<WContainerWidget>(), 1);
}

void CalendarW::setHeaderRange() {
    header_->setRange();
}

InterfaceCalendarHeaderW* CalendarW::addHeader(std::unique_ptr<InterfaceCalendarHeaderW> header) {
    return header_ = calendar_box_->addWidget(std::move(header));
}

InterfaceCalendarBodyW* CalendarW::addCalendarBodyDay(
    std::unique_ptr<InterfaceCalendarBodyW> calendar) {
    calendars_[Range::DAY] = calendar_box_->addWidget(std::move(calendar));
    calendars_[Range::DAY]->hide();
    return calendars_[Range::DAY];
}

InterfaceCalendarBodyW* CalendarW::addCalendarBodyWeek(
    std::unique_ptr<InterfaceCalendarBodyW> calendar) {
    range_ = Range::WEEK;
    return calendars_[Range::WEEK] = calendar_box_->addWidget(std::move(calendar));
}

InterfaceCalendarBodyW* CalendarW::addCalendarBodyMonth(
    std::unique_ptr<InterfaceCalendarBodyW> calendar) {
    calendars_[Range::MONTH] = calendar_box_->addWidget(std::move(calendar));
    calendars_[Range::MONTH]->hide();
    return calendars_[Range::MONTH];
}

void CalendarW::addConnections() {
    show_tree_button_->clicked().connect(this, &CalendarW::showTree);
    header_->rangeChanged().connect(this, &CalendarW::setCalendarRange);
    for (auto&& calendar : calendars_) {
        header_->selectedDateChanged().connect(calendar, &InterfaceCalendarBodyW::updateCalendar);
    }
}

void CalendarW::showTree() {
    if (tree_->isHidden()) {
        tree_->show();
        show_tree_button_->setText(Wt::WString("<"));
    } else {
        tree_->hide();
        show_tree_button_->setText(Wt::WString(">"));
    }
}

void CalendarW::setCalendarRange(Range range) {
    calendars_[range_]->hide();
    calendars_[range]->show();
    range_ = range;
}

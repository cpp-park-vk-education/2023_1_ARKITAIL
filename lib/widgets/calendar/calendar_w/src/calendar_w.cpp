#include "calendar_w.hpp"

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>

#include <map>
#include <memory>

#include "CalendarBodyW.hpp"
#include "Managers.hpp"
#include "SessionScopeMap.hpp"
#include "TreeW.hpp"
#include "WeekW.hpp"
#include "calendar_header_w.hpp"
#include "day_w.hpp"
#include "month_w.hpp"

CalendarW::CalendarW() {
    auto layout = setLayout(std::make_unique<Wt::WHBoxLayout>());

    auto tree_panel = layout->addWidget(std::make_unique<Wt::WContainerWidget>());
    tree_panel->setStyleClass("start-0");

    tree_panel_layout = tree_panel->setLayout(std::make_unique<Wt::WHBoxLayout>());

    calendar_box_ = layout->addWidget(std::make_unique<WContainerWidget>(), 1);
}

TreeW* CalendarW::addTree(std::unique_ptr<TreeW> tree) {
    tree_ = tree_panel_layout->addWidget(std::move(tree));

    // В дальнейшем метод setRoot будет вызываться по сигналу перехода на страницу
    auto mgr = SessionScopeMap::instance().get()->managers();
    auto node = mgr->node_manager()->get(mgr->user_manager()->get()->root_id);
    tree_->setRoot(*node);

    show_tree_button_ =
        tree_panel_layout->addWidget(std::make_unique<Wt::WPushButton>(Wt::WString(">")));
    show_tree_button_->setStyleClass("btn-light rounded-end rounded-0 border-start-0");
    return tree_;
}

ICalendarHeaderW* CalendarW::addHeader(std::unique_ptr<ICalendarHeaderW> header) {
    return header_ = calendar_box_->addWidget(std::move(header));
}

ICalendarBodyW* CalendarW::addCalendarBodyDay(std::unique_ptr<ICalendarBodyW> calendar) {
    calendars_[Range::DAY] = calendar_box_->addWidget(std::move(calendar));
    calendars_[Range::DAY]->hide();
    return calendars_[Range::DAY];
}

ICalendarBodyW* CalendarW::addCalendarBodyWeek(std::unique_ptr<ICalendarBodyW> calendar) {
    range_ = Range::WEEK;
    return calendars_[Range::WEEK] = calendar_box_->addWidget(std::move(calendar));
}

ICalendarBodyW* CalendarW::addCalendarBodyMonth(std::unique_ptr<ICalendarBodyW> calendar) {
    calendars_[Range::MONTH] = calendar_box_->addWidget(std::move(calendar));
    calendars_[Range::MONTH]->hide();
    return calendars_[Range::MONTH];
}

void CalendarW::addConnections() {
    show_tree_button_->clicked().connect(this, &CalendarW::showTree);
    header_->rangeChanged().connect(this, &CalendarW::setCalendarRange);

    // for (auto calendar : calendars_) {
    //     header_->selectedDateChanged().connect(calendar.second, &ICalendarBodyW::updateCalendar);
    // }
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

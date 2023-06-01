#include "OtherP.hpp"

#include "CalendarBodyW.hpp"
#include "Managers.hpp"
#include "SessionScopeMap.hpp"
#include "TreeW.hpp"
#include "WeekW.hpp"
#include "calendar_header_w.hpp"
#include "calendar_w.hpp"
#include "day_w.hpp"
#include "month_w.hpp"

OtherP::OtherP() {
    auto ss = SessionScopeMap::instance().get();

    calendar_ = addWidget(std::make_unique<CalendarW>());

    auto tree = calendar_->addTree(std::make_unique<TreeW>());

    auto mgr = ss->managers();
    auto node = mgr->node_manager()->get(mgr->user_manager()->get()->root_id);

    auto cm = ss->connections_mediator();

    ss->connections_mediator()->set_tree_root.add_receiver(tree, &TreeW::setRoot);

    cm->node_to_tree_other.add_receiver(tree, &TreeW::checkNode);
    cm->tree_to_header_other.add_sender(&tree->node_checked);
    cm->header_to_tree_other.add_receiver(tree, &TreeW::getRangeEvents);
    cm->tree_to_body_other.add_sender(&tree->events_getted);

    auto header =
        calendar_->addHeader(std::make_unique<CalendarHeaderW>())->addButtons()->addConnections();
    cm->tree_to_header_other.add_receiver(header, &ICalendarHeaderW::emitDates);
    cm->header_to_tree_other.add_sender(&header->selectedDateChanged());

    auto day_w = calendar_->addCalendarBodyDay(std::make_unique<DayW>());
    auto week_w = calendar_->addCalendarBodyWeek(std::make_unique<WeekW>());
    auto month_w = calendar_->addCalendarBodyMonth(std::make_unique<MonthW>());

    cm->tree_to_body_other.add_receiver(day_w, &ICalendarBodyW::updateCalendar);
    cm->tree_to_body_other.add_receiver(week_w, &ICalendarBodyW::updateCalendar);
    cm->tree_to_body_other.add_receiver(month_w, &ICalendarBodyW::updateCalendar);

    calendar_->addConnections();
}

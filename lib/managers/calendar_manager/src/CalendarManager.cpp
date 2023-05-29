#include <Wt/WDate.h>
#include <Wt/WDateTime.h>
#include <cstddef>
#include <memory>

#include "Calendar.hpp"
#include "CalendarManager.hpp"
#include "Directory.hpp"
#include "Event.hpp"
#include "DbManagers.hpp"
#include "IDbManagers.hpp"
#include "SessionScopeMap.hpp"

CalendarManager::CalendarManager(std::shared_ptr<IDbManagers> db) :
    db_(db) {}

CalendarSptr CalendarManager::get(size_t calendar_id) {
    return db_->calendar_dbm()->get(calendar_id);
}

size_t CalendarManager::add(CalendarSptr calendar, size_t directory_id) {
    auto mgr = SessionScopeMap::instance().get()->managers();

    User user = db_->user_dbm()->get();
    Directory parent_directory = mgr->directory_manager()->get(directory_id);

    if (!parent_directory.id || user.id != parent_directory.owner_id)
        return 0;

    Node parent_node = mgr->node_manager()->get(get(directory_id)->node_id);
    Node new_node = {0, parent_node.id, 0, parent_node.type};

    size_t new_node_id = mgr->node_manager()->add(new_node);

    if (!new_node_id)
        return 0;

    CalendarSptr new_calendar = calendar;
    calendar->node_id = new_node_id;

    return db_->calendar_dbm()->add(calendar);
}

void CalendarManager::update(CalendarSptr calendar) {
    db_->calendar_dbm()->add(calendar);
}

void CalendarManager::remove(size_t calendar_id) {
    db_->calendar_dbm()->remove(calendar_id);
}

std::vector<EventSptr> CalendarManager::getEvents(size_t calendar_id) {
    return db_->calendar_dbm()->getEvents(calendar_id);
}

std::vector<EventSptr> CalendarManager::getEventsByInterval(
    size_t calendar_id,
    Wt::WDateTime begin,
    Wt::WDateTime end) {

    std::vector<EventSptr> events;

    for (auto e : getEvents(calendar_id))
        if (e->end >= begin && e->start <= end)
            events.push_back(e);

    return events;
}


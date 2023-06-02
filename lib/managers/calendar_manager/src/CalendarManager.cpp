#include "CalendarManager.hpp"

#include <memory>

#include <Wt/WDate.h>
#include <Wt/WDateTime.h>

#include "Calendar.hpp"
#include "Directory.hpp"
#include "Event.hpp"
#include "DbManagers.hpp"
#include "IDbManagers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "User.hpp"

CalendarManager::CalendarManager(std::shared_ptr<IDbManagers> db) :
    db_(db) {}

CalendarSptr CalendarManager::get(size_t calendar_id) {
    return db_->calendar_dbm()->get(calendar_id);
}

size_t CalendarManager::add(CalendarSptr calendar, size_t directory_id) {
    auto mgr = SessionScopeMap::instance().get()->managers();

    UserSptr user = db_->user_dbm()->get();
    DirectorySptr parent_directory = mgr->directory_manager()->get(directory_id);

    if (!parent_directory->id || user->id != parent_directory->owner_id)
        return 0;

    NodeSptr parent_node = mgr->node_manager()->get(mgr->directory_manager()->get(directory_id)->node_id);
    NodeSptr new_node = std::make_shared<Node>(
        0, parent_node->id, 0, parent_node->owner_id,
        (parent_node->type & PUBLIC ? PUBLIC_CALENDAR : PRIVATE_CALENDAR));

    new_node->id = mgr->node_manager()->add(new_node);

    if (!new_node->id) 
        return 0;

    calendar->node_id = new_node->id;

    calendar->id = db_->calendar_dbm()->add(calendar);
    new_node->resource_id = calendar->id;
    db_->node_dbm()->update(new_node);

    return calendar->id;
}

void CalendarManager::update(CalendarSptr calendar) {
    db_->calendar_dbm()->add(calendar);
}

void CalendarManager::remove(size_t calendar_id) {
    db_->calendar_dbm()->remove(calendar_id);
}

std::vector<Event> CalendarManager::getEvents(size_t calendar_id) {
    return db_->calendar_dbm()->getEvents(calendar_id);
}

std::vector<Event> CalendarManager::getEventsByInterval(
    size_t calendar_id,
    Wt::WDateTime start,
    Wt::WDateTime end) {

    std::vector<Event> events;

    for (auto e : getEvents(calendar_id))
        if (e.end >= start && e.start <= end)
            events.push_back(e);

    return events;
}


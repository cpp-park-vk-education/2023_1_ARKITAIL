#include <Wt/WDate.h>
#include <Wt/WDateTime.h>
#include <memory>

#include "Calendar.hpp"
#include "CalendarManager.hpp"
#include "Event.hpp"
#include "DbManagers.hpp"
#include "IDbManagers.hpp"

CalendarManager::CalendarManager(std::shared_ptr<IDbManagers> db) :
    db_(db) {}

CalendarSptr CalendarManager::get(size_t calendar_id) {
    return db_->calendar_dbm()->get(calendar_id);
}

size_t CalendarManager::add(CalendarSptr calendar) {
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


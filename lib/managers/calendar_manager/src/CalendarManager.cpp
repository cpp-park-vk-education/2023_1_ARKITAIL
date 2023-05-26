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

CalendarSptr CalendarManager::get(int calendar_id) {
    return db_->calendar_dbm()->get(calendar_id);
}

int CalendarManager::add(CalendarSptr calendar) {
    return db_->calendar_dbm()->add(calendar);
}

void CalendarManager::update(CalendarSptr calendar) {
    db_->calendar_dbm()->add(calendar);
}

void CalendarManager::remove(int calendar_id) {
    db_->calendar_dbm()->remove(calendar_id);
}

std::vector<Event> CalendarManager::getEvents(int calendar_id) {
    return db_->calendar_dbm()->getEvents(calendar_id);
}

std::vector<Event> CalendarManager::getEventsByInterval(
    int calendar_id,
    Wt::WDateTime start,
    Wt::WDateTime end) {

    std::vector<Event> events;

    for (auto e : getEvents(calendar_id))
        if (e.end >= start && e.start <= end)
            events.push_back(e);

    return events;
}


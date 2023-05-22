#include <memory>

#include "Calendar.hpp"
#include "CalendarManager.hpp"
#include "Event.hpp"
#include "DbManagers.hpp"
#include "IDbManagers.hpp"

CalendarManager::CalendarManager(std::shared_ptr<IDbManagers> db) :
    db_(db) {}

const Calendar& CalendarManager::get(size_t calendar_id) {
    return db_->calendar_dbm()->get(calendar_id);
}

size_t CalendarManager::add(const Calendar& calendar) {
    return db_->calendar_dbm()->add(calendar);
}

void CalendarManager::update(const Calendar& calendar) {
    db_->calendar_dbm()->add(calendar);
}

void CalendarManager::remove(size_t calendar_id) {
    db_->calendar_dbm()->remove(calendar_id);
}

std::vector<Event> CalendarManager::getEvents(size_t calendar_id) {
    return db_->calendar_dbm()->getEvents(calendar_id);
}


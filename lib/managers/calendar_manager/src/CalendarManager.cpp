#include "Calendar.hpp"
#include "CalendarManager.hpp"
#include "Event.hpp"
#include "DbManagers.hpp"

const Calendar& CalendarManager::get(size_t calendar_id) {
    return *(new Calendar());
}

size_t CalendarManager::add(const Calendar& calendar) {
    return DbManagers::instance().calendar_dbm->add(calendar);
}

void CalendarManager::update(const Calendar& calendar) {
    DbManagers::instance().calendar_dbm->add(calendar);
}

void CalendarManager::remove(size_t calendar_id) {
    DbManagers::instance().calendar_dbm->remove(calendar_id);
}

std::vector<Event> CalendarManager::getEvents(size_t calendar_id) {
    return DbManagers::instance().calendar_dbm->getEvents(calendar_id);
}


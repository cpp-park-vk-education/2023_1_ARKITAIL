#include "Calendar.hpp"
#include "CalendarManager.hpp"
#include "Event.hpp"

const Calendar& CalendarManager::get(size_t calendar_id) {
    return *(new Calendar());
}

size_t CalendarManager::add(const Calendar& calendar) {
    return manager_->add(calendar);
}

void CalendarManager::update(const Calendar& calendar) {
    manager_->add(calendar);
}

void CalendarManager::remove(size_t calendar_id) {
    manager_->remove(calendar_id);
}

std::vector<Event> CalendarManager::getEvents(size_t calendar_id) {
    return manager_->getEvents(calendar_id);
}


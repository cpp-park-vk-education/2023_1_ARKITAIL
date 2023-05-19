#include <chrono>
#include <string>

#include "DbManagers.hpp"
#include "Event.hpp"
#include "EventManager.hpp"

const Event& EventManager::get(size_t event_id) {
    return DbManagers::instance().event_dbm->get(event_id);
}

size_t EventManager::add(const Event& event) {
    return DbManagers::instance().event_dbm->add(event);
}

void EventManager::update(const Event& event) {
    DbManagers::instance().event_dbm->update(event);
}

void EventManager::remove(size_t event_id) {
    DbManagers::instance().event_dbm->remove(event_id);
}

std::vector<Comment> EventManager::getComments(size_t event_id) {
    return DbManagers::instance().event_dbm->getComments(event_id);
}

std::chrono::time_point<EventManager::clock_t> EventManager::parseTime(std::string str_time) {
    // TODO(uma_op): IMPLEMENT ME
    return std::chrono::time_point<EventManager::clock_t>();
}


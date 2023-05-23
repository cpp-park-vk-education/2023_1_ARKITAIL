#include "EventManager.hpp"

#include <chrono>
#include <string>

#include "DbManagers.hpp"
#include "Event.hpp"
#include "IDbManagers.hpp"

EventManager::EventManager(IDbManagers* db) :
    db_(db) {}

const Event& EventManager::get(size_t event_id) {
    return db_->event_dbm()->get(event_id);
}

size_t EventManager::add(const Event& event) {
    return db_->event_dbm()->add(event);
}

void EventManager::update(const Event& event) {
    db_->event_dbm()->update(event);
}

void EventManager::remove(size_t event_id) {
    db_->event_dbm()->remove(event_id);
}

std::vector<Comment> EventManager::getComments(size_t event_id) {
    return db_->event_dbm()->getComments(event_id);
}

std::chrono::time_point<EventManager::clock_t> EventManager::parseTime(std::string str_time) {
    // TODO(uma_op): IMPLEMENT ME
    return std::chrono::time_point<EventManager::clock_t>();
}

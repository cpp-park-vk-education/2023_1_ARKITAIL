#include "EventManager.hpp"

#include <chrono>
#include <string>
#include <memory>

#include "DbManagers.hpp"
#include "Event.hpp"
#include "IDbManagers.hpp"

EventManager::EventManager(std::shared_ptr<IDbManagers> db) :
    db_(db) {}

<<<<<<< HEAD
EventSptr EventManager::get(size_t event_id) {
    return db_->event_dbm()->get(event_id);
}

size_t EventManager::add(EventSptr event) {
=======
const Event& EventManager::get(int event_id) {
    return db_->event_dbm()->get(event_id);
}

int EventManager::add(const Event& event) {
>>>>>>> origin/impl-lukyanov
    return db_->event_dbm()->add(event);
}

void EventManager::update(EventSptr event) {
    db_->event_dbm()->update(event);
}

void EventManager::remove(int event_id) {
    db_->event_dbm()->remove(event_id);
}

// std::vector<Comment> EventManager::getComments(int event_id) {
//     return db_->event_dbm()->getComments(event_id);
// }

std::chrono::time_point<EventManager::clock_t> EventManager::parseTime(std::string str_time) {
    // TODO(uma_op): IMPLEMENT ME
    return std::chrono::time_point<clock_t>();
}

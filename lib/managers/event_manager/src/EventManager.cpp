#include "EventManager.hpp"

#include <chrono>
#include <string>
#include <memory>

#include "DbManagers.hpp"
#include "Event.hpp"
#include "IDbManagers.hpp"

EventManager::EventManager(std::shared_ptr<IDbManagers> db) :
    db_(db) {}

EventSptr EventManager::get(int event_id) {
    return db_->event_dbm()->get(event_id);
}

int EventManager::add(EventSptr event) {
    return db_->event_dbm()->add(event);
}

void EventManager::update(EventSptr event) {
    db_->event_dbm()->update(event);
}

void EventManager::remove(int event_id) {
    db_->event_dbm()->remove(event_id);
}


#include <chrono>
#include <string>

#include "Event.hpp"
#include "EventManager.hpp"

const Event& EventManager::get(size_t event_id) {
    return manager_->get(event_id);
}

size_t EventManager::add(const Event& event) {
    return manager_->add(event);
}

void EventManager::update(const Event& event) {
    manager_->update(event);
}

void EventManager::remove(size_t event_id) {
    manager_->remove(event_id);
}

std::vector<Comment> EventManager::getComments(size_t event_id) {
    return manager_->getComments(event_id);
}

std::chrono::time_point<EventManager::clock_t> EventManager::parseTime(std::string str_time) {
    // TODO(uma_op): IMPLEMENT ME
    return std::chrono::time_point<EventManager::clock_t>();
}


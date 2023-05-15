#include <vector>

#include "Calendar.hpp"
#include "Event.hpp"
#include "UnmetDeps.hpp"
#include "Directory.hpp"
#include "Node.hpp"

const Directory& DirectoryDbManager::get(size_t) {
	return *(new Directory());  // dummy
}

size_t DirectoryDbManager::add(const Directory&) {
	return 0;
}

void DirectoryDbManager::update(const Directory&) {}
void DirectoryDbManager::remove(size_t) {}

std::vector<Directory> DirectoryDbManager::getChildren(size_t){
	return std::vector<Directory>();
}

const Node& NodeDbManager::get(size_t node_id) {
	return *(new Node());
}

size_t NodeDbManager::add(const Node& node) {
	return 0;
}

void NodeDbManager::update(const Node& node) {}
void NodeDbManager::remove(size_t node_id) {}

std::vector<Node> NodeDbManager::getChildren(size_t node_id) {
	return std::vector<Node>();
}

const Calendar& CalendarDbManager::get(size_t calendar_id) {
	return *(new Calendar());
}

size_t CalendarDbManager::add(const Calendar& calendar) {
	return 0;
}

void CalendarDbManager::update(const Calendar& calendar) {}
void CalendarDbManager::remove(size_t calendar_id) {}

std::vector<Event> CalendarDbManager::getEvents(size_t calendar_id) {
	return std::vector<Event>();
}

const User& UserDbManager::get() {
	return *(new User());
}

const Event& EventDbManager::get(size_t) {
	return *(new Event());
}

size_t EventDbManager::add(const Event& event) {
	return 0;
}

void EventDbManager::update(const Event& event) {}
void EventDbManager::remove(size_t event_id) {}

std::vector<Comment> EventDbManager::getComments(size_t event_id) {
	return std::vector<Comment>();
}


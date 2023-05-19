#include <chrono>
#include <vector>

#include "DbManagers.hpp"
#include "Comment.hpp"
#include "Event.hpp"
#include "EventDbManagerMock.hpp"

EventDbManagerMock::EventDbManagerMock() :
	data_(),
	aid_(1) {

	data_.emplace_back(0, 0, "", "", std::chrono::steady_clock::now(), std::chrono::steady_clock::now());
}

const Event& EventDbManagerMock::get(size_t event_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == event_id)
			return *e;
	
	return data_[0];
}

size_t EventDbManagerMock::add(const Event& event) {
	data_.emplace_back(
		aid_,
		event.calendar_id,
		event.name,
		event.description,
		event.begin_point,
		event.end_point
	);

	return aid_++;
}

void EventDbManagerMock::update(const Event& event) {
	for (auto e : data_)
		if (e.id == event.id)
			e = event;
}

void EventDbManagerMock::remove(size_t event_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == event_id)
			data_.erase(e);
}

std::vector<Comment> EventDbManagerMock::getComments(size_t event_id) {
	return DbManagers::instance().comment_dbm->getByEvent(event_id);
}

std::vector<Event> EventDbManagerMock::getByCalendar(size_t calendar_id) {
	std::vector<Event> events;

	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->calendar_id == calendar_id)
			events.push_back(*e);

	return events;
}


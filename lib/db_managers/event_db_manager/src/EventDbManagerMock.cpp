#include <chrono>
#include <memory>
#include <vector>

#include "DbManagers.hpp"
#include "Comment.hpp"
#include "DbMock.hpp"
#include "Event.hpp"
#include "EventDbManagerMock.hpp"

EventDbManagerMock::EventDbManagerMock(std::shared_ptr<DbMock> db) :
	db_(db),
	aid_(db->events.size()) {}

const Event& EventDbManagerMock::get(int event_id) {
	for (auto e = db_->events.begin() + 1; e != db_->events.end(); e++)
		if (e->id == event_id)
			return *e;
	
	return db_->events[0];
}

int EventDbManagerMock::add(const Event& event) {
	db_->events.emplace_back(
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
	for (auto e : db_->events)
		if (e.id == event.id)
			e = event;
}

void EventDbManagerMock::remove(int event_id) {
	for (auto e = db_->events.begin() + 1; e != db_->events.end(); e++)
		if (e->id == event_id)
			db_->events.erase(e);
}

// std::vector<Comment> EventDbManagerMock::getComments(int event_id) {
// 	std::vector<Comment> comments;

// 	for (auto e = db_->comments.begin() + 1; e != db_->comments.end(); e++)
// 		if (e->event_id == event_id)
// 			comments.push_back(*e);

// 	return comments;
// }

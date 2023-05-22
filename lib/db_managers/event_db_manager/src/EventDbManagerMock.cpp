#include <chrono>
#include <memory>
#include <vector>

#include <Wt/WDateTime.h>

#include "DbManagers.hpp"
#include "Comment.hpp"
#include "DbMock.hpp"
#include "Event.hpp"
#include "EventDbManagerMock.hpp"

EventDbManagerMock::EventDbManagerMock(std::shared_ptr<DbMock> db) :
	db_(db),
	aid_(db->events.size()) {

	db_->events.emplace_back(0, 0, "", "", Wt::WDateTime::currentDateTime(), Wt::WDateTime::currentDateTime());
	
}

EventSptr EventDbManagerMock::get(size_t event_id) {
	for (auto e = db_->events.begin() + 1; e != db_->events.end(); e++)
		if (e->id == event_id)
			return std::make_shared<Event>(*e);
	
	return std::make_shared<Event>(db_->events[0]);
}

size_t EventDbManagerMock::add(EventSptr event) {
	db_->events.emplace_back(
		aid_,
		event->calendar_id,
		event->summary,
		event->description,
		event->start,
		event->end
	);

	return aid_++;
}

void EventDbManagerMock::update(EventSptr event) {
	for (auto e : db_->events)
		if (e.id == event->id)
			e = *event;
}

void EventDbManagerMock::remove(size_t event_id) {
	for (auto e = db_->events.begin() + 1; e != db_->events.end(); e++)
		if (e->id == event_id)
			db_->events.erase(e);
}

std::vector<Comment> EventDbManagerMock::getComments(size_t event_id) {
	std::vector<Comment> comments;

	for (auto e = db_->comments.begin() + 1; e != db_->comments.end(); e++)
		if (e->event_id == event_id)
			comments.push_back(*e);

	return comments;
}


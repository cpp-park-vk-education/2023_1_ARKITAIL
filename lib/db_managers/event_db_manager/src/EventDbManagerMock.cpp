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
	aid_(db->events.size()) {}

EventSptr EventDbManagerMock::get(int event_id) {
	for (auto e = db_->events.begin() + 1; e != db_->events.end(); e++)
		if (e->id == event_id)
			return std::make_shared<Event>(*e);
	
	return std::make_shared<Event>(db_->events[0]);
}

int EventDbManagerMock::add(EventSptr event) {
	db_->events.emplace_back(
		aid_,
		event->calendar_id,
		event->summary,
		event->description,
    event->location,
		event->start,
		event->end,
    event->stamp,
    event->frequency,
    event->interval,
    event->until
	);

	return aid_++;
}

void EventDbManagerMock::update(EventSptr event) {
	for (auto e : db_->events)
		if (e.id == event->id)
			e = *event;
}

void EventDbManagerMock::remove(int event_id) {
	for (auto e = db_->events.begin() + 1; e != db_->events.end(); e++)
		if (e->id == event_id)
			db_->events.erase(e);
}

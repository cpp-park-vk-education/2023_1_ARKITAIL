#include "CalendarDbManagerMock.hpp"
#include "DbManagers.hpp"
#include "DbMock.hpp"
#include "EventDbManagerMock.hpp"
#include "CalendarDbManagerMock.hpp"
#include "Calendar.hpp"
#include "Event.hpp"

CalendarDbManagerMock::CalendarDbManagerMock(std::shared_ptr<DbMock> db) :
	db_(db),
	aid_(){
	
	aid_ = db_->calendars.size();
}

const Calendar& CalendarDbManagerMock::get(int calendar_id) {
	for (auto e = db_->calendars.begin() + 1; e != db_->calendars.end(); e++)
		if (e->id == calendar_id)
			return *e;
	
	return db_->calendars[0];
}

int CalendarDbManagerMock::add(const Calendar& calendar) {
	db_->calendars.emplace_back(
		aid_,
		calendar.node_id,
		calendar.owner_id,
		calendar.name,
		calendar.description
	);

	return aid_++;
}

void CalendarDbManagerMock::update(const Calendar& calendar) {
	for (auto e : db_->calendars)
		if (e.id == calendar.id)
			e = calendar;
}

void CalendarDbManagerMock::remove(int calendar_id) {
	for (auto e = db_->calendars.begin() + 1; e != db_->calendars.end(); e++)
		if (e->id == calendar_id)
			db_->calendars.erase(e);
}

std::vector<Event> CalendarDbManagerMock::getEvents(int calendar_id) {
	std::vector<Event> events;

	for (auto e = db_->events.begin() + 1; e != db_->events.end(); e++)
		if (e->calendar_id == calendar_id)
			events.push_back(*e);

	return events;
}



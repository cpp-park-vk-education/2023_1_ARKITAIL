#include "CalendarDbManagerMock.hpp"
#include "DbManagers.hpp"
#include "DbMock.hpp"
#include "EventDbManagerMock.hpp"
#include "CalendarDbManagerMock.hpp"
#include "Calendar.hpp"
#include "Event.hpp"

CalendarDbManagerMock::CalendarDbManagerMock(std::shared_ptr<DbMock> db) :
	db_(),
	aid_(){
	
	db_->calendars.emplace_back(0, 0, 0, "", "");

	db_->calendars.emplace_back(1, 8, 0, "PrivateCalendar", "desc");
	db_->calendars.emplace_back(2, 9, 0, "PrivateCalendar", "desc");
	db_->calendars.emplace_back(3, 11, 0, "PublicCalendar", "desc");
	db_->calendars.emplace_back(4, 12, 0, "PublicCalendar", "desc");
	db_->calendars.emplace_back(5, 20, 1, "PrivateCalendar", "desc");
	db_->calendars.emplace_back(6, 21, 1, "PrivateCalendar", "desc");
	db_->calendars.emplace_back(7, 23, 1, "PublicCalendar", "desc");
	db_->calendars.emplace_back(8, 24, 1, "PublicCalendar", "desc");

	aid_ = db_->calendars.size();
}

const Calendar& CalendarDbManagerMock::get(size_t calendar_id) {
	for (auto e = db_->calendars.begin() + 1; e != db_->calendars.end(); e++)
		if (e->id == calendar_id)
			return *e;
	
	return db_->calendars[0];
}

size_t CalendarDbManagerMock::add(const Calendar& calendar) {
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

void CalendarDbManagerMock::remove(size_t calendar_id) {
	for (auto e = db_->calendars.begin() + 1; e != db_->calendars.end(); e++)
		if (e->id == calendar_id)
			db_->calendars.erase(e);
}

std::vector<Event> CalendarDbManagerMock::getEvents(size_t calendar_id) {
	std::vector<Event> events;

	for (auto e = db_->events.begin() + 1; e != db_->events.end(); e++)
		if (e->calendar_id == calendar_id)
			events.push_back(*e);

	return events;
}



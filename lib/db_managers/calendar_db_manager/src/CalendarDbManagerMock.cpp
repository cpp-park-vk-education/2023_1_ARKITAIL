#include "CalendarDbManagerMock.hpp"
#include "DbManagers.hpp"
#include "EventDbManagerMock.hpp"
#include "CalendarDbManagerMock.hpp"
#include "Calendar.hpp"
#include "Event.hpp"

CalendarDbManagerMock::CalendarDbManagerMock() :
	data_(),
	aid_(1){
	
	data_.emplace_back(0, 0, 0, "", "");
}

const Calendar& CalendarDbManagerMock::get(size_t calendar_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == calendar_id)
			return *e;
	
	return data_[0];
}

size_t CalendarDbManagerMock::add(const Calendar& calendar) {
	data_.emplace_back(
		aid_,
		calendar.node_id,
		calendar.owner_id,
		calendar.name,
		calendar.description
	);

	return aid_++;
}

void CalendarDbManagerMock::update(const Calendar& calendar) {
	for (auto e : data_)
		if (e.id == calendar.id)
			e = calendar;
}

void CalendarDbManagerMock::remove(size_t calendar_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == calendar_id)
			data_.erase(e);
}

std::vector<Event> CalendarDbManagerMock::getEvents(size_t calendar_id) {
	return DbManagers::instance().event_dbm->getByCalendar(calendar_id);
}



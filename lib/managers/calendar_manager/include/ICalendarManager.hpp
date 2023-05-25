#pragma once

#include <chrono>
#include <vector>

#include "Calendar.hpp"
#include "Event.hpp"

class ICalendarManager {
public:
	virtual const Calendar& get(size_t calendar_id) = 0;
	virtual size_t add(const Calendar& calendar) = 0;  // Maybe returns error code 
	virtual void remove(size_t calendar_id) = 0;
	virtual void update(const Calendar& calendar) = 0;

	virtual std::vector<Event> getEvents(size_t calendar_id) = 0;
	
	virtual std::vector<Event> getEventsByInterval(
		size_t calendar_id,
		std::chrono::time_point<std::chrono::steady_clock> begin,
		std::chrono::time_point<std::chrono::steady_clock> end) = 0;

};


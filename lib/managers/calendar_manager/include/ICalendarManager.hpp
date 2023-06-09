#pragma once

#include <Wt/WDateTime.h>
#include <chrono>
#include <vector>

#include "Calendar.hpp"
#include "Event.hpp"

class ICalendarManager {
public:
	virtual CalendarSptr get(size_t calendar_id) = 0;
	virtual size_t add(CalendarSptr calendar, size_t directory_id) = 0;  // Maybe returns error code 
	virtual void remove(size_t calendar_id) = 0;
	virtual void update(CalendarSptr calendar) = 0;

	virtual std::vector<Event> getEvents(size_t calendar_id) = 0;
	virtual std::vector<Event> getEventsByInterval(
      size_t calendar_id,
		  Wt::WDateTime start,
		  Wt::WDateTime end) = 0;
};


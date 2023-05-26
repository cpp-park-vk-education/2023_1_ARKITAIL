#pragma once

#include <Wt/WDateTime.h>
#include <chrono>
#include <vector>

#include "Calendar.hpp"
#include "Event.hpp"

class ICalendarManager {
public:
	virtual CalendarSptr get(int calendar_id) = 0;
	virtual int add(CalendarSptr calendar) = 0;
	virtual void remove(int calendar_id) = 0;
	virtual void update(CalendarSptr calendar) = 0;

	virtual std::vector<Event> getEvents(int calendar_id) = 0;
	virtual std::vector<Event> getEventsByInterval(
      int calendar_id,
		  Wt::WDateTime start,
		  Wt::WDateTime end) = 0;
};


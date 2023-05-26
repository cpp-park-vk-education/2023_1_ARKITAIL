#pragma once

#include <Wt/WDateTime.h>
#include <chrono>
#include <vector>

#include "Calendar.hpp"
#include "Event.hpp"

class ICalendarManager {
public:
	virtual CalendarSptr get(int calendar_id) = 0;
	virtual int add(CalendarSptr calendar) = 0;  // Maybe returns error code 
	virtual void remove(int calendar_id) = 0;
	virtual void update(CalendarSptr calendar) = 0;

	virtual std::vector<EventSptr> getEvents(int calendar_id) = 0;
	
	virtual std::vector<EventSptr> getEventsByInterval(
      int calendar_id,
		  Wt::WDateTime begin,
		  Wt::WDateTime end) = 0;
};


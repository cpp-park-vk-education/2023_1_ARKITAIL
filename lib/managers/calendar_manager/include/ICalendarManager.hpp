#pragma once

#include <vector>

#include "Calendar.hpp"
#include "Event.hpp"

class ICalendarManager {
public:
	virtual const Calendar& get(int calendar_id) = 0;
	virtual int add(const Calendar& calendar) = 0;  // Maybe returns error code 
	virtual void remove(int calendar_id) = 0;
	virtual void update(const Calendar& calendar) = 0;

	virtual std::vector<Event> getEvents(int calendar_id) = 0;

};


#pragma once

#include "Calendar.hpp"
#include "Event.hpp"
#include <vector>

class ICalendarManager {
public:
	virtual const Calendar& get(size_t calendar_id) = 0;
	virtual void add(const Calendar& calendar) = 0;  // Maybe returns error code 
	virtual void remove(size_t calendar_id) = 0;
	virtual void update(const Calendar& calendar) = 0;

	virtual void addEvent(size_t calendar_id, const Event& event) = 0;
	virtual std::vector<const Calendar&> getEvents(size_t calendar_id) = 0;

};


#pragma once

#include <vector>

#include "ICalendarManager.hpp"
#include "Event.hpp"
#include "Calendar.hpp"

class CalendarManager : public ICalendarManager {
public:
    const Calendar& get(size_t) override;
	size_t add(const Calendar&) override;
	void update(const Calendar&) override;
	void remove(size_t) override;

    std::vector<Event> getEvents(size_t calendar_id) override;

};


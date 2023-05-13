#pragma once

#include <vector>

#include "Event.hpp"
#include "Calendar.hpp"

class CalendarManager {
public:
    static void addEvent(const Calendar& calendar, const Event& event);
    static std::vector<Event> getEvents(const Calendar& calendar);

};


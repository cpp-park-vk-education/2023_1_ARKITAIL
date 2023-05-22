#pragma once

#include <vector>

#include "Calendar.hpp"
#include "Event.hpp"

class ICalendarDbManager {
public:
    virtual CalendarSptr get(size_t) = 0;
    virtual size_t add(CalendarSptr) = 0;
    virtual void update(CalendarSptr) = 0;
    virtual void remove(size_t) = 0;

    virtual std::vector<EventSptr> getEvents(size_t) = 0;

};


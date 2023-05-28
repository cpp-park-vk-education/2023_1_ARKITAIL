#pragma once

#include <vector>

#include "Calendar.hpp"
#include "Event.hpp"

class ICalendarDbManager {
public:
    virtual CalendarSptr get(int calendar_id) = 0;
    virtual int add(CalendarSptr) = 0;
    virtual void update(CalendarSptr) = 0;
    virtual void remove(int calendar_id) = 0;

    virtual std::vector<Event> getEvents(int calendar_id) = 0;
};


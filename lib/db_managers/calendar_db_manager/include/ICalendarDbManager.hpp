#pragma once

#include <vector>

#include "Calendar.hpp"
#include "Event.hpp"

class ICalendarDbManager {
public:
    virtual const Calendar& get(int calendar_id) = 0;
    virtual int add(const Calendar&) = 0;
    virtual void update(const Calendar&) = 0;
    virtual void remove(int calendar_id) = 0;

    virtual std::vector<Event> getEvents(int calendar_id) = 0;

};


#pragma once

#include ""

class ICalendarDbManager {
public:
    virtual const Calendar& get(size_t) = 0;
    virtual size_t add(const Calendar&) = 0;
    virtual void update(const Calendar&) = 0;
    virtual void remove(size_t) = 0;

    virtual std::vector<Event> getEvents(size_t) = 0;
};


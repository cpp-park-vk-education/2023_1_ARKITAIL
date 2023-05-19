#pragma once

#include "ICalendarDbManager.hpp"

class CalendarDbManagerMock : public ICalendarDbManager {
public:
    CalendarDbManagerMock();

    const Calendar& get(size_t);
    size_t add(const Calendar&);
    void update(const Calendar&);
    void remove(size_t);

    std::vector<Event> getEvents(size_t);

private:
    std::vector<Calendar> data_;
    size_t aid_;

};


#pragma once

#include <memory>

#include "ICalendarDbManager.hpp"

#include "Calendar.hpp"
#include "DbMock.hpp"
#include "Event.hpp"

class CalendarDbManagerMock : public ICalendarDbManager {
public:
    CalendarDbManagerMock(std::shared_ptr<DbMock> db);

    CalendarSptr get(size_t);
    size_t add(CalendarSptr);
    void update(CalendarSptr);
    void remove(size_t);

    std::vector<EventSptr> getEvents(size_t);

private:
    std::shared_ptr<DbMock> db_;
    size_t aid_;

};


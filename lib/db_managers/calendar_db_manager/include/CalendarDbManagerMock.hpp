#pragma once

#include <memory>

#include "DbMock.hpp"
#include "ICalendarDbManager.hpp"

class CalendarDbManagerMock : public ICalendarDbManager {
public:
    CalendarDbManagerMock(std::shared_ptr<DbMock> db);

    const Calendar& get(size_t);
    size_t add(const Calendar&);
    void update(const Calendar&);
    void remove(size_t);

    std::vector<Event> getEvents(size_t);

private:
    std::shared_ptr<DbMock> db_;
    size_t aid_;

};


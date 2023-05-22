#pragma once

#include <memory>

#include "DbMock.hpp"
#include "ICalendarDbManager.hpp"

class CalendarDbManagerMock : public ICalendarDbManager {
public:
    CalendarDbManagerMock(std::shared_ptr<DbMock> db);

    const Calendar& get(int);
    int add(const Calendar&);
    void update(const Calendar&);
    void remove(int);

    std::vector<Event> getEvents(int);

private:
    std::shared_ptr<DbMock> db_;
    int aid_;

};


#pragma once

#include <memory>

#include "DbMock.hpp"
#include "ICalendarDbManager.hpp"

class CalendarDbManagerMock : public ICalendarDbManager {
public:
    CalendarDbManagerMock(std::shared_ptr<DbMock> db);

    const Calendar& get(int calendar_id);
    int add(const Calendar&);
    void update(const Calendar&);
    void remove(int calendar_id);

    std::vector<Event> getEvents(int calendar_id);

private:
    std::shared_ptr<DbMock> db_;
    int aid_;

};


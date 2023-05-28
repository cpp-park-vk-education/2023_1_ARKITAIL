#pragma once

#include <memory>

#include "ICalendarDbManager.hpp"

#include "Calendar.hpp"
#include "DbMock.hpp"
#include "Event.hpp"

class CalendarDbManagerMock : public ICalendarDbManager {
public:
    CalendarDbManagerMock(std::shared_ptr<DbMock> db);

    CalendarSptr get(int calendar_id) override;
    int add(CalendarSptr) override;
    void update(CalendarSptr) override;
    void remove(int calendar_id) override;

    std::vector<Event> getEvents(int calendar_id) override;

private:
    std::shared_ptr<DbMock> db_;
    int aid_;

};


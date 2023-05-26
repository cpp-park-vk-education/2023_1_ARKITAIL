#pragma once

#include <Wt/WDateTime.h>
#include <vector>
#include <memory>

#include "ICalendarManager.hpp"
#include "Event.hpp"
#include "Calendar.hpp"
#include "IDbManagers.hpp"

class CalendarManager : public ICalendarManager {
public:
    CalendarManager(std::shared_ptr<IDbManagers> db);

    CalendarSptr get(int) override;
    int add(CalendarSptr) override;
    void update(CalendarSptr) override;
    void remove(int) override;

    std::vector<EventSptr> getEvents(int calendar_id) override;
    std::vector<EventSptr> getEventsByInterval(
        int calendar_id,
	      Wt::WDateTime begin,
	      Wt::WDateTime end) override;

private:
    std::shared_ptr<IDbManagers> db_;

};


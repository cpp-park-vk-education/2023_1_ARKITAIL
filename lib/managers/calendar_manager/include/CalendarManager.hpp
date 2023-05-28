#pragma once

#include <Wt/WDateTime.h>
#include <cstddef>
#include <vector>
#include <memory>

#include "ICalendarManager.hpp"
#include "Event.hpp"
#include "Calendar.hpp"
#include "IDbManagers.hpp"

class CalendarManager : public ICalendarManager {
public:
    CalendarManager(std::shared_ptr<IDbManagers> db);

    CalendarSptr get(size_t) override;
    size_t add(CalendarSptr, size_t) override;
    void update(CalendarSptr) override;
    void remove(size_t) override;

    std::vector<Event> getEvents(size_t calendar_id) override;
    std::vector<Event> getEventsByInterval(
        size_t calendar_id,
	      Wt::WDateTime start,
	      Wt::WDateTime end) override;

private:
    std::shared_ptr<IDbManagers> db_;

};


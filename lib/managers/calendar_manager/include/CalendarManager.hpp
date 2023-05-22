#pragma once

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
    size_t add(CalendarSptr) override;
    void update(CalendarSptr) override;
    void remove(size_t) override;

    std::vector<EventSptr> getEvents(size_t calendar_id) override;

private:
    std::shared_ptr<IDbManagers> db_;

};


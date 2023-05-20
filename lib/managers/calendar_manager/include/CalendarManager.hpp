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

    const Calendar& get(size_t) override;
    size_t add(const Calendar&) override;
    void update(const Calendar&) override;
    void remove(size_t) override;

    std::vector<Event> getEvents(size_t calendar_id) override;

private:
    std::shared_ptr<IDbManagers> db_;

};


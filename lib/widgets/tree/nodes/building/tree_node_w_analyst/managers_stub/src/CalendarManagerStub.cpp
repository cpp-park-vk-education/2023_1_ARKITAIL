#include "CalendarManagerStub.hpp"

#include <vector>

#include "Calendar.hpp"

CalendarManagerStub::CalendarManagerStub(std::vector<Calendar> calendars) :
    calendars_(calendars) {}

CalendarSptr CalendarManagerStub::get(size_t calendar_id) {
    for (auto e = calendars_.begin() + 1; e != calendars_.end(); e++)
        if (e->id == calendar_id)
            return std::make_shared<Calendar>(*e);

    return std::make_shared<Calendar>(calendars_[0]);
}

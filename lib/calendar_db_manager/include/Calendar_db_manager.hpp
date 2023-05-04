#pragma once

#include "Calendar_db_model.hpp"

class calendars_manager {
public:
    calendars addCalendar(calendars);
    calendars deleteCalendar(int id);
    calendars upgradeCalendar(calendars);
    calendars getCalendar(int id);
};
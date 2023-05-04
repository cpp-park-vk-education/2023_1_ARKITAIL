#pragma once

#include "Event_db_model.hpp"

class event_manager {
public:
    events addEvent(events);
    events deleteEvent(int id);
    events upgradeEvent(events);
    events getEvent(int id);
};
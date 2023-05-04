#pragma once

#include "base_for_all.hpp"
#include "Calendar_db_model.hpp"

class events {
public:
    std::string name;
    std::time_t time_start;
    std::time_t time_end;
    std::string description;
    dbo::collection< dbo::ptr<calendars> > calendar;


    template<class Action>
    void persist(Action& a) {
        dbo::field(a, name, "name");
        dbo::field(a, time_start, "time_start");
        dbo::field(a, time_end, "time_end");
        dbo::field(a, description, "description");
        dbo::hasMany(a, calendar, dbo::ManyToOne, "event");
    }
};

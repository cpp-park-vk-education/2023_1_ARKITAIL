#pragma once

#include "base_for_all.hpp"
#include "Calendar_db_model.hpp"

class tags {
public:
    std::string name;
    dbo::collection<dbo::ptr<calendars>> calendar;


    template<class Action>
    void persist(Action& a) {
        dbo::field(a, name, "name");
        dbo::hasMany(a, calendar, dbo::ManyToMany, "calendar_tags");
    }
};
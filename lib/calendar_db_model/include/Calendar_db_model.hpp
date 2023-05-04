#pragma once

#include "base_for_all.hpp"
#include "Node_db_model.hpp"
#include "Event_db_model.hpp"
#include "Tag_db_model.hpp"
#include "User_db_model.hpp"

class calendars {
public:
    dbo::collection< dbo::ptr<users> > user; // Owner
    dbo::collection<dbo::ptr<tags>> tag; // tags
    bool visibility; // visibility
    std::string name; // name
    dbo::ptr<events> event; //event
    dbo::ptr<nodes> node; //p_node


    template<class Action>
    void persist(Action& a) {
        dbo::field(a, name, "name");
        dbo::hasMany(a, user, dbo::ManyToOne, "calendar");
        dbo::belongsTo(a, event, "event");
        dbo::field(a, visibility, "visubility");
        dbo::hasMany(a, tag, dbo::ManyToMany, "calendar_tags");
        dbo::belongsTo(a, node, "node");
    }
};
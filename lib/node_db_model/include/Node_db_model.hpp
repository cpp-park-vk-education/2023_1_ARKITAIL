#pragma once

#include "base_for_all.hpp"

enum class Type {
    Directory = 0,
    Calendar = 1,
    Mount = 2
};

class nodes {
public:
    Type type;
    dbo::ptr<nodes> parent;
    int resource_id;


    template<class Action>
    void persist(Action& a) {
        dbo::field(a, type, "type");
        dbo::belongsTo(a, parent, "parent");
        dbo::field(a, resource_id, "resource_id");
    }
};
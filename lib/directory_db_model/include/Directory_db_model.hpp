#pragma once

#include "base_for_all.hpp"
#include "Node_db_model.hpp"

class directory {
public:
    std::string name;
    std::string description;
    dbo::ptr<nodes> node;

    template<class Action>
    void persist(Action& a) {
        dbo::field(a, name, "name");
        dbo::field(a, description, "description");
        dbo::belongsTo(a, node, "node");
    }
};
#pragma once

#include <cstddef>
#include <string>

class Calendar {
public:
    Calendar();

    size_t id;
    size_t node_id;
    size_t owner_id;

    std::string name;
    std::string description;

};

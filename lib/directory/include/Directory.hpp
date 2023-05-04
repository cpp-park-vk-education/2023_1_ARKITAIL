#pragma once

#include <cstddef>
#include <string>

class Direcotory {
public:
    Direcotory();

    size_t id;
    size_t node_id;
    size_t owner_id;

    std::string name;
    std::string description;

};


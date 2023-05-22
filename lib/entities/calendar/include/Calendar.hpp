#pragma once

#include <cstddef>
#include <string>

class Calendar {
  public:
    Calendar();
    Calendar(
        int id,
        int node_id,
        int owner_id,
        std::string name,
        std::string description
    );

    int id;
    int node_id;
    int owner_id;

    std::string name;
    std::string description;
};

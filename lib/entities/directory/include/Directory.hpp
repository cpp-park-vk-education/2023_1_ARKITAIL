#pragma once

#include <cstddef>
#include <string>

class Directory {
public:
    Directory();
    Directory(size_t id, size_t node_id, size_t owner_id, std::string name, std::string description);

    size_t id;
    size_t node_id;
    size_t owner_id;

    std::string name;
    std::string description;

};

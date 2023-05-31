#pragma once

#include <cstddef>
#include <vector>
#include <string>

class Profile {
public:
    Profile();
    Profile(size_t id, size_t node_id, size_t owner_id, std::vector<size_t> nodes, std::string name);

    size_t id;
    size_t node_id;
    size_t owner_id;

    std::vector<size_t> nodes;

    std::string name;

};


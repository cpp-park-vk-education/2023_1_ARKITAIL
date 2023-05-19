#pragma once

#include <cstddef>
#include <vector>

class Profile {
public:
    Profile();
    Profile(size_t id, size_t node_id, size_t owner_id, std::vector<size_t> nodes);

    size_t id;
    size_t node_id;
    size_t owner_id;

    std::vector<size_t> nodes;

};


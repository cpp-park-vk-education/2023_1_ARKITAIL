#pragma once

#include <cstddef>
#include <vector>
#include <string>
#include <memory>

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

using ProfileSptr = std::shared_ptr<Profile>;


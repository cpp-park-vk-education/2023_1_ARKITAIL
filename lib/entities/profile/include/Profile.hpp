#pragma once

#include <memory>
#include <vector>

class Profile;
using ProfileSptr = std::shared_ptr<Profile>;

class Profile {
public:
    Profile() = default;
    explicit Profile(
        int id,
        int node_id,
        int owner_id,
        std::vector<int> nodes);

    int id;
    int node_id;
    int owner_id;

    std::vector<int> nodes;

};


#pragma once

#include <memory>
#include <vector>
#include <string>

class Profile;
using ProfileSptr = std::shared_ptr<Profile>;

class Profile {
public:
    Profile() = default;
    explicit Profile(const Profile& other);
    Profile(int id, int node_id, int owner_id, std::vector<int> nodes, std::string name);

    int id;
    int node_id;
    int owner_id;

    std::vector<int> nodes;
    std::string name;

};

using ProfileSptr = std::shared_ptr<Profile>;

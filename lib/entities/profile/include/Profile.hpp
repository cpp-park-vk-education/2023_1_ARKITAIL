#pragma once

#include <cstddef>
#include <vector>

class Profile {
public:
    Profile();
    Profile(int id, int node_id, int owner_id, std::vector<int> nodes);

    int id;
    int node_id;
    int owner_id;

    std::vector<int> nodes;

};


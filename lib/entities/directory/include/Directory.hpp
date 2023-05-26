#pragma once

#include <cstddef>
#include <string>

class Directory {
public:
    Directory();
    Directory(int id, int node_id, int owner_id, std::string name, std::string description);

    int id;
    int node_id;
    int owner_id;

    std::string name;
    std::string description;

};


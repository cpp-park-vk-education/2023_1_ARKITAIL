#pragma once

#include <memory>
#include <string>

class Directory;
using DirectorySptr = std::shared_ptr<Directory>;

class Directory {
public:
    Directory() = default;
    Directory(int id, int node_id, int owner_id, std::string name, std::string description);

    int id;
    int node_id;
    int owner_id;

    std::string name;
    std::string description;

};


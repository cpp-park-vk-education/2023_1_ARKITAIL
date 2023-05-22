#pragma once

#include <cstddef>
#include <string>

class Tag {
public:
    Tag();
    Tag(size_t id, std::string name);
    
    size_t id;
    std::string name;

};


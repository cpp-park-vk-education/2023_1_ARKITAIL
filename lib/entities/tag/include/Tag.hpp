#pragma once

#include <cstddef>
#include <string>

class Tag {
public:
    Tag();
    Tag(int id, std::string name);
    
    int id;
    std::string name;

};


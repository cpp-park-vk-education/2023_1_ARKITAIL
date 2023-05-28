#pragma once

#include <vector>

#include "Directory.hpp"

class IDirectoryDbManager {
public:
    virtual DirectorySptr get(int directory_id) = 0;
    virtual int add(DirectorySptr) = 0;
    virtual void update(DirectorySptr) = 0;
    virtual void remove(int directory_id) = 0;
};


#pragma once

#include <vector>

#include "Directory.hpp"

class IDirectoryDbManager {
public:
    virtual const Directory& get(size_t) = 0;
    virtual size_t add(const Directory&) = 0;
    virtual void update(const Directory&) = 0;
    virtual void remove(size_t) = 0;

};


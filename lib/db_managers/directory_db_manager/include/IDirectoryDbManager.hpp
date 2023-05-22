#pragma once

#include <vector>

#include "Directory.hpp"

class IDirectoryDbManager {
public:
    virtual const Directory& get(int) = 0;
    virtual int add(const Directory&) = 0;
    virtual void update(const Directory&) = 0;
    virtual void remove(int) = 0;

};


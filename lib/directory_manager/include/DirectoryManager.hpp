#pragma once

#include <vector>

#include "Directory.hpp"
#include "Event.hpp"

class DirectoryManager {
public:
    DirectoryManager();

    std::vector<Event> getEvents(const Directory& directory);
    void remove(const Directory& directory);
    void add(const Directory& directory);
    void update(const Directory& directory);

};


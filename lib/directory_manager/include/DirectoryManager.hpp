#pragma once

#include <vector>

#include "Directory.hpp"
#include "Event.hpp"

class DirectoryManager {
public:
    static std::vector<Event> getEvents(const Directory& directory);
    static void remove(const Directory& directory);
    static void add(const Directory& directory, const Directory& parent);
    static void update(const Directory& directory);

};


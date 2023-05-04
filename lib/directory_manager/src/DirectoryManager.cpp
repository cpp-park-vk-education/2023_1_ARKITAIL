#include <vector>

#include "Directory.hpp"
#include "DirectoryManager.hpp"
#include "Event.hpp"

std::vector<Event> DirectoryManager::getEvents(const Directory& directory) {
    return std::vector<Event>();
}

void DirectoryManager::remove(const Directory& directory) {}
void DirectoryManager::add(const Directory& directory, const Directory& parent) {}
void DirectoryManager::update(const Directory& directory) {}


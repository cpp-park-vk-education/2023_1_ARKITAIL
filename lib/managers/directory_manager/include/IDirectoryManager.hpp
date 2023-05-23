#pragma once

#include <vector>

#include "Directory.hpp"
#include "Event.hpp"

class IDirectoryManager {
public:
	virtual Directory get(size_t directory_id) = 0;
	virtual size_t add(const Directory& directory, size_t directory_id) = 0;
	virtual void update(const Directory& directory) = 0;
	virtual void remove(size_t directory_id) = 0;

	virtual std::vector<Event> getEvents(size_t directory_id) = 0;
	
};


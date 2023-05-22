#pragma once

#include <vector>

#include "Directory.hpp"
#include "Event.hpp"

class IDirectoryManager {
public:
	virtual const Directory& get(int directory_id) = 0;
	virtual int add(const Directory& directory, int directory_id) = 0;
	virtual void update(const Directory& directory) = 0;
	virtual void remove(int directory_id) = 0;

	virtual std::vector<Event> getEvents(int directory_id) = 0;
	
};


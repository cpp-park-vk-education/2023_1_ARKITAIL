#pragma once

#include <vector>

#include "Directory.hpp"
#include "Event.hpp"

class IDirectoryManager {
public:
	virtual DirectorySptr get(int directory_id) = 0;
	virtual int add(DirectorySptr directory, int directory_id) = 0;
	virtual void update(DirectorySptr directory) = 0;
	virtual void remove(int directory_id) = 0;

	virtual std::vector<Event> getEvents(int directory_id) = 0;
	
};


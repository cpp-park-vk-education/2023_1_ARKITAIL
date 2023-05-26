#pragma once

#include <vector>

#include "Directory.hpp"
#include "Event.hpp"

class IDirectoryManager {
public:
<<<<<<< HEAD
	virtual Directory get(size_t directory_id) = 0;
	virtual size_t add(const Directory& directory, size_t directory_id) = 0;
=======
	virtual const Directory& get(int directory_id) = 0;
	virtual int add(const Directory& directory, int directory_id) = 0;
>>>>>>> origin/impl-lukyanov
	virtual void update(const Directory& directory) = 0;
	virtual void remove(int directory_id) = 0;

<<<<<<< HEAD
	virtual std::vector<EventSptr> getEvents(size_t directory_id) = 0;
=======
	virtual std::vector<Event> getEvents(int directory_id) = 0;
>>>>>>> origin/impl-lukyanov
	
};


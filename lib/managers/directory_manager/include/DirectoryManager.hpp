#pragma once

#include <vector>

#include "IDirectoryManager.hpp"
#include "Directory.hpp"
#include "Event.hpp"

class DirectoryManager : public IDirectoryManager {
public:
	const Directory& get(size_t directory_id) override;
	size_t add(const Directory& directory, size_t directory_id) override;
	void update(const Directory& directory) override;
	void remove(size_t directory_id) override;

	std::vector<Event> getEvents(size_t directory_id) override;

};


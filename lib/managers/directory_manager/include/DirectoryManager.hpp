#pragma once

#include <vector>
#include <memory>

#include "IDbManagers.hpp"
#include "IDirectoryManager.hpp"
#include "Directory.hpp"
#include "Event.hpp"

class DirectoryManager : public IDirectoryManager {
public:
	DirectoryManager(std::shared_ptr<IDbManagers> db);

	Directory get(size_t directory_id) override;
	size_t add(const Directory& directory, size_t directory_id) override;
	void update(const Directory& directory) override;
	void remove(size_t directory_id) override;

	std::vector<Event> getEvents(size_t directory_id) override;

private:
	std::shared_ptr<IDbManagers> db_;

};


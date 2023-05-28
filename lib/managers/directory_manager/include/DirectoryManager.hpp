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

	DirectorySptr get(int directory_id) override;
	int add(DirectorySptr directory, int directory_id) override;
	void update(DirectorySptr directory) override;
	void remove(int directory_id) override;

	std::vector<Event> getEvents(int directory_id) override;

private:
	std::shared_ptr<IDbManagers> db_;

};


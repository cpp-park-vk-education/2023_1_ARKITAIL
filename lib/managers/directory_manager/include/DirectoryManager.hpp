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

<<<<<<< HEAD
	Directory get(size_t directory_id) override;
	size_t add(const Directory& directory, size_t directory_id) override;
=======
	const Directory& get(int directory_id) override;
	int add(const Directory& directory, int directory_id) override;
>>>>>>> origin/impl-lukyanov
	void update(const Directory& directory) override;
	void remove(int directory_id) override;

<<<<<<< HEAD
	std::vector<EventSptr> getEvents(size_t directory_id) override;
=======
	std::vector<Event> getEvents(int directory_id) override;
>>>>>>> origin/impl-lukyanov

private:
	std::shared_ptr<IDbManagers> db_;

};


#pragma once

#include "IDbManagers.hpp"
#include "ITagManager.hpp"
#include <memory>

class TagManager : public ITagManager {
public:
	TagManager(std::shared_ptr<IDbManagers> db);

	Tag get(size_t tag_id);
	size_t add(const Tag& tag);
	void remove(size_t tag_id);

private:
	std::shared_ptr<IDbManagers> db_;

};


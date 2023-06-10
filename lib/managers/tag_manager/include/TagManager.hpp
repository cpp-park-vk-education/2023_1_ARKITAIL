#pragma once

#include "IDbManagers.hpp"
#include "ITagManager.hpp"
#include "Node.hpp"
#include "Tag.hpp"
#include <memory>
#include <vector>

class TagManager : public ITagManager {
public:
	TagManager(std::shared_ptr<IDbManagers> db);

	TagSptr get(size_t tag_id) override;
	size_t add(TagSptr tag) override;
	void remove(size_t tag_id) override;

	TagSptr find(const std::string& tag_name) override;
	std::vector<NodeSptr> nodeByTag(int tag_id) override;

private:
	std::shared_ptr<IDbManagers> db_;

};


#pragma once

#include <memory>
#include <vector>

#include "DbMock.hpp"
#include "ITagDbManager.hpp"

class TagDbManagerMock : public ITagDbManager {
public:
	TagDbManagerMock(std::shared_ptr<DbMock> db);

	const Tag& get(size_t tag_id);
	size_t add(const Tag& tag);
	void update(const Tag& tag);
	void remove(size_t tag_id);
	std::vector<Node> NodeByTag(size_t tag_id);
	Tag find(const std::string title);
	
private:
	std::shared_ptr<DbMock> db_;
	size_t aid_;

};


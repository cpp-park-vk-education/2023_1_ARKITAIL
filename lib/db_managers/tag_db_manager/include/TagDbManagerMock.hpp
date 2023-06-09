#pragma once

#include <memory>
#include <vector>

#include "DbMock.hpp"
#include "ITagDbManager.hpp"
#include "Node.hpp"
#include "Tag.hpp"

class TagDbManagerMock : public ITagDbManager {
public:
	TagDbManagerMock(std::shared_ptr<DbMock> db);

	TagSptr get(int tag_id) override;
	int add(TagSptr tag) override;
	void remove(int tag_id) override;

	TagSptr find(const std::string& tag_name) override;
	std::vector<NodeSptr> nodeByTag(int tag_id) override;
	
private:
	std::shared_ptr<DbMock> db_;
	int aid_;

};


#pragma once

#include <memory>
#include <vector>

#include "DbMock.hpp"
#include "ITagDbManager.hpp"
#include "Tag.hpp"

class TagDbManagerMock : public ITagDbManager {
public:
	TagDbManagerMock(std::shared_ptr<DbMock> db);

	TagSptr get(int tag_id) override;
	int add(TagSptr tag) override;
	void update(TagSptr tag) override;
	void remove(int tag_id) override;
	std::vector<Node> NodeByTag(int tag_id) override;
	
private:
	std::shared_ptr<DbMock> db_;
	int aid_;

};


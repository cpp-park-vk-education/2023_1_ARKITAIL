#pragma once

#include <vector>

#include "ITagDbManager.hpp"

class TagDbManagerMock : public ITagDbManager {
public:
	TagDbManagerMock();

	const Tag& get(int tag_id);
	int add(const Tag& tag);
	void update(const Tag& tag);
	void remove(int tag_id);
	
private:
	std::vector<Tag> data_;
	int aid_;

};


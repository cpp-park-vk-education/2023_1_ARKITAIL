#pragma once

#include <vector>

#include "ITagDbManager.hpp"

class TagDbManagerMock : public ITagDbManager {
public:
	TagDbManagerMock();

	const Tag& get(size_t tag_id);
	size_t add(const Tag& tag);
	void update(const Tag& tag);
	void remove(size_t tag_id);
	
private:
	std::vector<Tag> data_;
	size_t aid_;

};


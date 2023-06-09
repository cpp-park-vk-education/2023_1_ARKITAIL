#pragma once

#include <vector>

#include "Node.hpp"
#include "Tag.hpp"

class ITagManager {
public:
	virtual TagSptr get(size_t tag_id) = 0;
	virtual size_t add(TagSptr tag) = 0;
	virtual void remove(size_t tag_id) = 0;

	virtual TagSptr find(const std::string& tag_name) = 0;
	virtual std::vector<NodeSptr> nodeByTag(int tag_id) = 0;

};


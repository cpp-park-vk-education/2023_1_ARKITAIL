#pragma once

#include <vector>

#include "Tag.hpp"
#include "Node.hpp"

class ITagDbManager {
public:
	virtual const Tag& get(size_t tag_id) = 0;
	virtual size_t add(const Tag& tag) = 0;
	virtual void update(const Tag& tag) = 0;
	virtual void remove(size_t tag_id) = 0;
	virtual std::vector<Node> NodeByTag(size_t tag) = 0;
	virtual Tag find(const std::string title) = 0;

};


#pragma once

#include <vector>

#include "Tag.hpp"
#include "Node.hpp"

class ITagDbManager {
public:
	virtual TagSptr get(int tag_id) = 0;
	virtual int add(TagSptr tag) = 0;
	virtual void update(TagSptr tag) = 0;
	virtual void remove(int tag_id) = 0;
  
	virtual TagSptr find(const std::string& tag_name) = 0;
	virtual std::vector<Node> NodeByTag(int tag) = 0;

};


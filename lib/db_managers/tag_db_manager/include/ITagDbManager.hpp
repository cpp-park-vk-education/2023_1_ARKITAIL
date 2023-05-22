#pragma once

#include "Tag.hpp"

class ITagDbManager {
public:
	virtual const Tag& get(int tag_id) = 0;
	virtual int add(const Tag& tag) = 0;
	virtual void update(const Tag& tag) = 0;
	virtual void remove(int tag_id) = 0;

};


#pragma once

#include "Tag.hpp"

class ITagDbManager {
public:
	virtual const Tag& get(size_t tag_id) = 0;
	virtual size_t add(const Tag& tag) = 0;
	virtual void update(const Tag& tag) = 0;
	virtual void remove(size_t tag_id) = 0;

};

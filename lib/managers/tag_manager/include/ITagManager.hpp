#pragma once

#include "Tag.hpp"

class ITagManager {
public:
	virtual Tag get(size_t tag_id) = 0;
	virtual size_t add(const Tag& tag) = 0;
	virtual void remove(size_t tag_id) = 0;
	virtual Tag find(const std::string title) = 0;

};


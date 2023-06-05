#pragma once

#include "Tag.hpp"

class ITagManager {
public:
	virtual TagSptr get(size_t tag_id) = 0;
	virtual size_t add(TagSptr tag) = 0;
	virtual void remove(size_t tag_id) = 0;

	virtual Tag find(const std::string& tag_name) = 0;

};


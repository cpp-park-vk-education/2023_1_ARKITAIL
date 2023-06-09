#pragma once

#include "Tag.hpp"

class ITagDbManager {
public:
	virtual TagSptr get(int tag_id) = 0;
	virtual int add(TagSptr tag) = 0;
	virtual void update(TagSptr tag) = 0;
	virtual void remove(int tag_id) = 0;

};


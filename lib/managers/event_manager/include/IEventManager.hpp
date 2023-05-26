#pragma once

#include <string_view>
#include <vector>

#include "Event.hpp"
#include "Comment.hpp"

class IEventManager {
public:
	virtual EventSptr get(int) = 0;
	virtual int add(EventSptr) = 0;
	virtual void update(EventSptr) = 0;
	virtual void remove(int) = 0;

};


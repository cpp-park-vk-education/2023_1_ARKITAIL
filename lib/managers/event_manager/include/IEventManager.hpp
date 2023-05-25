#pragma once

#include <chrono>
#include <string_view>
#include <vector>

#include "Event.hpp"
#include "Comment.hpp"

class IEventManager {
public:
	using clock_t = std::chrono::steady_clock;

	virtual EventSptr get(size_t) = 0;
	virtual size_t add(EventSptr) = 0;
	virtual void update(EventSptr) = 0;
	virtual void remove(size_t) = 0;

	virtual std::vector<Comment> getComments(size_t) = 0;
	virtual std::chrono::time_point<clock_t> parseTime(std::string) = 0;

};


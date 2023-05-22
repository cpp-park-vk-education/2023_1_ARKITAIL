#pragma once

#include <chrono>
#include <string_view>
#include <vector>

#include "Event.hpp"
#include "Comment.hpp"

class IEventManager {
public:
	using clock_t = std::chrono::steady_clock;

	virtual const Event& get(int) = 0;
	virtual int add(const Event&) = 0;
	virtual void update(const Event&) = 0;
	virtual void remove(int) = 0;

	virtual std::vector<Comment> getComments(int) = 0;
	virtual std::chrono::time_point<clock_t> parseTime(std::string) = 0;

};


#pragma once

#include <chrono>
#include <string_view>
#include <vector>

#include "Event.hpp"
#include "Comment.hpp"

class IEventManager {
public:
	using clock_t = std::chrono::steady_clock;

<<<<<<< HEAD
	virtual EventSptr get(size_t) = 0;
	virtual size_t add(EventSptr) = 0;
	virtual void update(EventSptr) = 0;
	virtual void remove(size_t) = 0;
=======
	virtual const Event& get(int) = 0;
	virtual int add(const Event&) = 0;
	virtual void update(const Event&) = 0;
	virtual void remove(int) = 0;
>>>>>>> origin/impl-lukyanov

	//virtual std::vector<Comment> getComments(int) = 0;
	virtual std::chrono::time_point<clock_t> parseTime(std::string) = 0;

};


#include "Event.hpp"

Event::Event() :
	id(),
	calendar_id(),
	name(),
	description(),
	begin_point(),
	end_point() {}

Event::Event(
    size_t id,
    size_t calendar_id,
    std::string name,
    std::string description,
    std::chrono::time_point<std::chrono::steady_clock> begin_point,
    std::chrono::time_point<std::chrono::steady_clock> end_point
) : 
	id(id),
	calendar_id(calendar_id),
	name(name),
	description(description),
	begin_point(begin_point),
	end_point(end_point) {}


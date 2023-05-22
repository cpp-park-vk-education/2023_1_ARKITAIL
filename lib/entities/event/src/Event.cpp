#include "Event.hpp"

Event::Event() :
	id(),
	calendar_id(),
	name(),
	description(),
	begin_point(),
	end_point() {}

Event::Event(
    int id,
    int calendar_id,
    std::string name,
    std::string description,
    std::string begin_point,
    std::string end_point
) : 
	id(id),
	calendar_id(calendar_id),
	name(name),
	description(description),
	begin_point(begin_point),
	end_point(end_point) {}


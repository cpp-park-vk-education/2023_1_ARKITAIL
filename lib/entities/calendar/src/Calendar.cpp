#include "Calendar.hpp"

Calendar::Calendar() :
	id(), 
	node_id(),
	owner_id(), 
	name(),
	description() {}

Calendar::Calendar(
    size_t id,
    size_t node_id,
    size_t owner_id,
    std::string name,
    std::string description
) :
	id(id),
	node_id(node_id),
	owner_id(owner_id),
	name(name),
	description(description) {}


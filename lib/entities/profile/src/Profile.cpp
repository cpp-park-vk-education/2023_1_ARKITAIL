#include "Profile.hpp"

Profile::Profile() :
	id(),
	node_id(),
	owner_id(),
	nodes() {}


Profile::Profile(size_t id, size_t node_id, size_t owner_id, std::vector<size_t> nodes) :
	id(id),
	node_id(node_id),
	owner_id(owner_id),
	nodes(nodes) {}


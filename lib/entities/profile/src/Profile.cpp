#include "Profile.hpp"

Profile::Profile() :
	id(),
	node_id(),
	owner_id(),
	nodes(),
	name() {}

Profile::Profile(const Profile& other) :
	id(other.id),
	node_id(other.node_id),
	owner_id(other.owner_id),
	nodes(other.nodes),
	name(other.name) {}

Profile::Profile(size_t id, size_t node_id, size_t owner_id, std::vector<size_t> nodes, std::string name) :
	id(id),
	node_id(node_id),
	owner_id(owner_id),
	nodes(nodes),
	name(name) {}


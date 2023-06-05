#include "Profile.hpp"

Profile::Profile(const Profile& other) :
	id(other.id),
	node_id(other.node_id),
	owner_id(other.owner_id),
	nodes(other.nodes),
	name(other.name) {}

Profile::Profile(int id, int node_id, int owner_id, std::vector<int> nodes, std::string name) :
	id(id),
	node_id(node_id),
	owner_id(owner_id),
	nodes(nodes),
	name(name) {}


#include "Profile.hpp"

Profile::Profile() :
	id(),
	node_id(),
	owner_id(),
	nodes() {}


Profile::Profile(int id, int node_id, int owner_id, std::vector<int> nodes) :
	id(id),
	node_id(node_id),
	owner_id(owner_id),
	nodes(nodes) {}


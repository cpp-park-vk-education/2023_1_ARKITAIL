#include "Profile.hpp"

Profile::Profile(
    int id,
    int node_id,
    int owner_id,
    std::vector<int> nodes)
    : id(id),
      node_id(node_id),
	    owner_id(owner_id),
	    nodes(std::move(nodes)) {
}


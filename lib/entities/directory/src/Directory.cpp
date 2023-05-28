#include "Directory.hpp"

Directory::Directory(int id, int node_id, int owner_id, std::string name, std::string description) :
	id(id),
	node_id(node_id),
	owner_id(owner_id),
	name(std::move(name)),
	description(std::move(description)) {}
	

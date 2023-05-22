#include "Directory.hpp"

Directory::Directory() :
	id(),
	node_id(),
	owner_id(),
	name(),
	description() {}

Directory::Directory(int id, int node_id, int owner_id, std::string name, std::string description) :
	id(id),
	node_id(node_id),
	owner_id(owner_id),
	name(name),
	description(description) {}
	

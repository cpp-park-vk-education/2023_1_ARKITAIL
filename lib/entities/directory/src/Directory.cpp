#include "Directory.hpp"

Directory::Directory() :
	id(),
	node_id(),
	owner_id(),
	name(),
	description() {}

Directory::Directory(size_t id, size_t node_id, size_t owner_id, std::string name, std::string description) :
	id(id),
	node_id(node_id),
	owner_id(owner_id),
	name(name),
	description(description) {}
	

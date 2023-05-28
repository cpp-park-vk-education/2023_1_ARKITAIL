#include "Tag.hpp"

Tag::Tag(int id, std::string name) :
	id(id),
	name(std::move(name)) {
}


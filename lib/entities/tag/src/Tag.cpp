#include "Tag.hpp"

Tag::Tag(int id, std::string name) :
	id(id),
	name(std::move(name)) {
}


bool Tag::operator==(const Tag& a) const {
  return std::tie(id, name) == std::tie(a.id, a.name);
}

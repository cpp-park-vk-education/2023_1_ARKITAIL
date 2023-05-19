#include <string>

#include "Comment.hpp"

Comment::Comment() :
	id(),
	event_id(),
	owner_id(),
	text() {}

Comment::Comment(size_t id, size_t event_id, size_t owner_id, std::string text) :
	id(id),
	event_id(event_id),
	owner_id(owner_id),
	text(text) {}


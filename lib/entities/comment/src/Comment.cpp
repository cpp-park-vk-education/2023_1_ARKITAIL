#include <string>

#include "Comment.hpp"

Comment::Comment() :
	id(),
	event_id(),
	owner_id(),
	text() {}

Comment::Comment(int id, int event_id, int owner_id, std::string text) :
	id(id),
	event_id(event_id),
	owner_id(owner_id),
	text(text) {}


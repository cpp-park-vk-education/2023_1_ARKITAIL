#include "Comment.hpp"

Comment::Comment(int id, int event_id, std::string text) :
	id(id),
	event_id(event_id),
	//owner_id(owner_id),
	text(std::move(text)) {}


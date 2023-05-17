#pragma once

#include <cstddef>
#include <string>

class Comment {
public:
	Comment();

	size_t id;
	size_t event_id;
	size_t owner_id;

	std::string text;

};


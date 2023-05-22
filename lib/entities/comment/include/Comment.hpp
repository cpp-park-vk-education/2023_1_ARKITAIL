#pragma once

#include <cstddef>
#include <string>

class Comment {
public:
	Comment();
	Comment(int id, int event_id, int owner_id, std::string text);

	int id;
	int event_id;
	int owner_id;

	std::string text;

};


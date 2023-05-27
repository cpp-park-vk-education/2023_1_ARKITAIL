#pragma once

#include <memory>
#include <string>

class Comment;
using CommentSptr = std::shared_ptr<Comment>;

class Comment {
public:
	Comment() = default;
	Comment(int id, int event_id, std::string text);

	int id;
	int event_id;

	std::string text;

};


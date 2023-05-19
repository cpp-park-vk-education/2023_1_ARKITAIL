#pragma once

#include <vector>

#include "Comment.hpp"

class ICommentDbManager {
public:
	virtual const Comment& get(size_t comment_id) = 0;
	virtual size_t add(const Comment& comment) = 0;
	virtual void update(const Comment& comment) = 0;
	virtual void remove(size_t comment_id) = 0;

	virtual std::vector<Comment> getByEvent(size_t event_id) = 0;  // mock assistance

};


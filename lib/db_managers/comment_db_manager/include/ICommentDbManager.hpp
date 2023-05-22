#pragma once

#include <vector>

#include "Comment.hpp"

class ICommentDbManager {
public:
	virtual const Comment& get(int comment_id) = 0;
	virtual int add(const Comment& comment) = 0;
	virtual void update(const Comment& comment) = 0;
	virtual void remove(int comment_id) = 0;

};


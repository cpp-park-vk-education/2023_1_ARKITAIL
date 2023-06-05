#pragma once

#include "Comment.hpp"

class ICommentDbManager {
public:
	virtual CommentSptr get(int comment_id) = 0;
	virtual int add(CommentSptr comment) = 0;
  virtual void update(CommentSptr comment) = 0;
	virtual void remove(int comment_id) = 0;

};


#pragma once

#include "Comment.hpp"
#include "ICommentDbManager.hpp"

class CommentDbManagerMock : public ICommentDbManager {
public:
	CommentDbManagerMock();

	const Comment& get(int comment_id);
	int add(const Comment& comment);
	void update(const Comment& comment);
	void remove(int comment_id);

private:
	std::vector<Comment> data_;
	int aid_;

};


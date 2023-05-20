#pragma once

#include "Comment.hpp"
#include "ICommentDbManager.hpp"

class CommentDbManagerMock : public ICommentDbManager {
public:
	CommentDbManagerMock();

	const Comment& get(size_t comment_id);
	size_t add(const Comment& comment);
	void update(const Comment& comment);
	void remove(size_t comment_id);

private:
	std::vector<Comment> data_;
	size_t aid_;

};


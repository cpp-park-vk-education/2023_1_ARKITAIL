#pragma once

#include <vector>

#include "Comment.hpp"
#include "ICommentDbManager.hpp"

class CommentDbManagerMock : public ICommentDbManager {
public:
	CommentDbManagerMock();

	CommentSptr get(int comment_id) override;
	int add(CommentSptr comment) override;
  void update(CommentSptr comment) override;
	void remove(int comment_id) override;

private:
	std::vector<Comment> data_;
	int aid_;

};


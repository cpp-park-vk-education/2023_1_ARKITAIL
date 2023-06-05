#pragma once

#include "Comment.hpp"
#include "ICommentDbManager.hpp"
#include "Session.hpp"

class CommentDbManager: public ICommentDbManager {
public:
  CommentDbManager() = delete;
  explicit CommentDbManager(Session& session);

  int add(CommentSptr comment) override;
  void remove(int comment_id) override;
  void update(CommentSptr comment) override;
  CommentSptr get(int comment_id) override;

private:
  Session& session_;
  
};


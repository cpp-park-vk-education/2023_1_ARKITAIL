#pragma once

#include <Wt/Dbo/Session.h>

#include "Comment.hpp"
#include "DbModels.hpp"
#include "ICommentDbManager.hpp"

class CommentDbManager: public ICommentDbManager {
public:
  CommentDbManager(Wt::Dbo::Session &session) : session_(session) {}

  int add(CommentSptr comment) override;
  void remove(int comment_id) override;
  void update(CommentSptr comment) override;
  CommentSptr get(int comment_id) override;

private:
  int id_;
  Wt::Dbo::Session &session_;
};

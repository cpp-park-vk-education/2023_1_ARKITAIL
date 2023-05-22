#pragma once

#include "mainModel.hpp"
#include "ICommentDbManager.hpp"


class CommentDbManager: ICommentDbManager {
public:
  CommentDbManager(dbo::Session &session) : session_(session) {}

  int add(const Comment&);
  void remove(int comment_id);
  const Comment& get(int comment_id);


private:
  int id_;
  dbo::Session &session_;
};
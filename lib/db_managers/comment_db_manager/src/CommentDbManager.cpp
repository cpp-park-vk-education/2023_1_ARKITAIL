#include "CommentDbManager.hpp"

int CommentDbManager::add(const Comment &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<Comments> comment{new Comments()};
  comment->text = ret.text;
  comment->event = session_.find<Events>().where("id = ?").bind(ret.event_id);

  dbo::ptr<Comments> commentPtr = session_.add(std::move(comment));
  session_.flush();
  transaction.commit();
  id_ = commentPtr.id();
  return id_;
}

void CommentDbManager::remove(int comment_id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Comments> comment =
      session_.find<Comments>().where("id = ?").bind(comment_id);
  if (!comment) {
    return;
  }
  comment.remove();
  transaction.commit();
}

const Comment& CommentDbManager::get(int comment_id) {
  dbo::Transaction transaction(session_);

  Comment ret;
  dbo::ptr<Comments> comment =
      session_.find<Comments>().where("id = ?").bind(comment_id);
  if (!comment) {
    return ret;
  }
  ret.text = comment->text;
  ret.event_id = comment->event.id();

  transaction.commit();

  return ret;
}
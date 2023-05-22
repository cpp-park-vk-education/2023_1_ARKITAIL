#include "commentDbManager.hpp"

int CommentManager::Add(RetComm &ret) {
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

void CommentManager::Remove(int id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Comments> comment =
      session_.find<Comments>().where("id = ?").bind(id);
  if (!comment) {
    return;
  }
  comment.remove();
  transaction.commit();
}

RetComm CommentManager::Get(int id) {
  dbo::Transaction transaction(session_);

  RetComm ret;
  dbo::ptr<Comments> comment =
      session_.find<Comments>().where("id = ?").bind(id);
  if (!comment) {
    ret.name = "error";
    return ret;
  }
  ret.text = comment->text;
  ret.event_id = comment->event.id();

  transaction.commit();

  return ret;
}
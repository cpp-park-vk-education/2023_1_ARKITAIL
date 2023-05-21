#include "commentDbManager.hpp"

int CommentManager::add(Ret_Comm &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<comments> comment{new comments()};
  comment->name = ret.name;
  comment->text = ret.text;
  comment->event = session_.find<events>().where("id = ?").bind(ret.event_id);

  dbo::ptr<comments> commentPtr = session_.add(std::move(comment));
  id = commentPtr.id();
  transaction.commit();

  return id;
}

void CommentManager::remove(const int id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<comments> comment =
      session_.find<comments>().where("id = ?").bind(id);

  comment.remove();
  transaction.commit();
}

Ret_Comm CommentManager::get(const int id) {
  dbo::Transaction transaction(session_);

  Ret_Comm ret;
  dbo::ptr<comments> comment =
      session_.find<comments>().where("id = ?").bind(id);
  ret.name = comment->name;
  ret.text = comment->text;
  ret.event_id = comment->event.id();

  transaction.commit();

  return ret;
}
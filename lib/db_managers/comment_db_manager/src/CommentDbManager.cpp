#include "CommentDbManager.hpp"

#include <memory>

#include <Wt/Dbo/Transaction.h>

#include "DbModels.hpp"

int CommentDbManager::add(CommentSptr comment) {
  Wt::Dbo::Transaction transaction(session_);

  std::unique_ptr<db::Comment> db_comment_unique
      = std::make_unique<db::Comment>();
  db_comment_unique->text = comment->text;
  db_comment_unique->event
     = session_.find<db::Event>().where("id = ?").bind(comment->event_id);

  db::CommentPtr db_comment = session_.add(std::move(db_comment_unique));
  session_.flush();

  transaction.commit();

  id_ = db_comment.id();
  return id_;
}

void CommentDbManager::remove(int comment_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::CommentPtr db_comment =
      session_.find<db::Comment>().where("id = ?").bind(comment_id);

  if (!db_comment) {
    return;
  }

  db_comment.remove();

  transaction.commit();
}

void CommentDbManager::update(CommentSptr comment) {
  // TODO(Antiho)
}

CommentSptr CommentDbManager::get(int comment_id) {
  Wt::Dbo::ptr<db::Comment> db_comment =
      session_.find<db::Comment>().where("id = ?").bind(comment_id);

  if (!db_comment) {
    return nullptr;
  }

  Comment comment;
  comment.text = db_comment->text;
  comment.event_id = db_comment->event.id();
  comment.id = comment_id;

  return std::make_shared<Comment>(std::move(comment));
}

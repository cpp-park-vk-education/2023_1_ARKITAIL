#include "tagDbManager.hpp"

int TagManager::Add(RetTag &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<Tags> tag{new Tags()};
  tag->name = ret.name;

  dbo::ptr<Tags> tagPtr = session_.add(std::move(tag));
  session_.flush();
  transaction.commit();
  id_ = tagPtr.id();
  return id_;
}

void TagManager::Remove(int id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Tags> tag = session_.find<Tags>().where("id = ?").bind(id);
  if (!tag) {
    return;
  }
  tag.remove();
  transaction.commit();
}
RetTag TagManager::Get(int id) {
  dbo::Transaction transaction(session_);

  RetTag ret;
  dbo::ptr<Tags> tag = session_.find<Tags>().where("id = ?").bind(id);
  if (!tag) {
    ret.name = "error";
    return ret;
  }
  ret.name = tag->name;

  transaction.commit();
  return ret;
}

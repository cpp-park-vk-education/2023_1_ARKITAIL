#include "TagDbManager.hpp"

int TagDbManager::add(const Tag &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<Tags> tag{new Tags()};
  tag->name = ret.name;

  dbo::ptr<Tags> tagPtr = session_.add(std::move(tag));
  session_.flush();
  transaction.commit();
  id_ = tagPtr.id();
  return id_;
}

void TagDbManager::remove(int tag_id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Tags> tag = session_.find<Tags>().where("id = ?").bind(tag_id);
  if (!tag) {
    return;
  }
  tag.remove();
  transaction.commit();
}
const Tag& TagDbManager::get(int tag_id) {
  dbo::Transaction transaction(session_);

  Tag ret;
  dbo::ptr<Tags> tag = session_.find<Tags>().where("id = ?").bind(tag_id);
  if (!tag) {
    ret.name = "error";
    return ret;
  }
  ret.name = tag->name;

  transaction.commit();
  return ret;
}

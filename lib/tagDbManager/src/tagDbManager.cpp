#include "tagDbManager.hpp"

int TagManager::add(Ret_Tag &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<tags> tag{new tags()};
  tag->name = ret.name;

  dbo::ptr<tags> tagPtr = session_.add(std::move(tag));
  session_.flush();
  transaction.commit();
  id = tagPtr.id();
  return id;

  return id;
}
void TagManager::remote(const int id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<tags> tag = session_.find<tags>().where("id = ?").bind(id);
  if (!tag) {
    return;
  }
  tag.remove();
  transaction.commit();
}
Ret_Tag TagManager::get(const int id) {
  dbo::Transaction transaction(session_);

  Ret_Tag ret;
  dbo::ptr<tags> tag = session_.find<tags>().where("id = ?").bind(id);
  if (!tag) {
    ret.name = "error";
    return ret;
  }
  ret.name = tag->name;

  transaction.commit();
  return ret;
}

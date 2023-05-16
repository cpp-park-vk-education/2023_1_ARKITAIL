#include "tagDbManager.hpp"

int TagManager::add(Ret_Tag &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<tags> tag{new tags()};
  tag->name = ret.name;

  dbo::ptr<tags> tagPtr = session_.add(std::move(tag));
  id = tagPtr.id();
  transaction.commit();

  return id;
}
void TagManager::remote(const int id) {}
Ret_Tag TagManager::get(const int id) {}

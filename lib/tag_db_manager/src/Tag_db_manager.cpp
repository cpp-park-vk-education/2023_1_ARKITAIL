#include "Tag_db_manager.hpp"

int tag_manager::addTag(Ret_Tag &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<tags> tag{new tags()};
  tag->name = ret.name;

  dbo::ptr<tags> tagPtr = session_.add(std::move(tag));
  id = tagPtr.id();
  transaction.commit();

  return id;
}
void tag_manager::remoteTag(const int id) {}
Ret_Tag tag_manager::getTag(const int id) {}

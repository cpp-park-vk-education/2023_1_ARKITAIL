#include "profileDbManager.hpp"

int ProfileManager::add(Ret_Prof &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<profiles> profile{new profiles()};
  profile->name = ret.name;
  profile->node = session_.find<nodes>().where("id = ?").bind(ret.node_id);

  dbo::ptr<profiles> profilePtr = session_.add(std::move(profile));
      profilePtr = session_.find<profiles>().where("name = ?").bind(ret.name);

  id = profilePtr.id();
  transaction.commit();

  return id;
}

void ProfileManager::remove(const int id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<profiles> profile =
      session_.find<profiles>().where("id = ?").bind(id);

  profile.remove();
  transaction.commit();
}

Ret_Prof ProfileManager::get(const int id) {
  dbo::Transaction transaction(session_);

  Ret_Prof ret;
  dbo::ptr<profiles> profile =
      session_.find<profiles>().where("id = ?").bind(id);
  ret.name = profile->name;
  ret.node_id = profile->node.id();

  transaction.commit();

  return ret;
}
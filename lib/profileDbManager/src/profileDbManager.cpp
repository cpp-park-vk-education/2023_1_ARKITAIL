#include "profileDbManager.hpp"

int ProfileManager::Add(RetProf &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<Profiles> profile{new Profiles()};
  profile->user = session_.find<Users>().where("id = ?").bind(ret.owner_id);
  profile->node = session_.find<Nodes>().where("id = ?").bind(ret.node_id);

  dbo::ptr<Profiles> profilePtr = session_.add(std::move(profile));
  session_.flush();
  transaction.commit();
  id_ = profilePtr.id();
  return id_;
}

void ProfileManager::Remove(int id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Profiles> profile =
      session_.find<Profiles>().where("id = ?").bind(id);
  if (!profile) {
    return;
  }
  profile.remove();
  transaction.commit();
}

RetProf ProfileManager::Get(int id) {
  dbo::Transaction transaction(session_);

  RetProf ret;
  dbo::ptr<Profiles> profile =
      session_.find<Profiles>().where("id = ?").bind(id);
  if (!profile) {
    return ret;
  }
  ret.owner_id = profile->user.id();
  ret.node_id = profile->node.id();

  transaction.commit();

  return ret;
}
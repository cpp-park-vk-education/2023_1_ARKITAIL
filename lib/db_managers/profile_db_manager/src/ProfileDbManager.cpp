#include "ProfileDbManager.hpp"

int ProfileDbManager::add(const Profile &ret) {
  dbo::Transaction transaction(session_);

  std::unique_ptr<Profiles> profile{new Profiles()};
  profile->user = session_.find<Users>().where("id = ?").bind(ret.owner_id);
  profile->node = session_.find<Nodes>().where("id = ?").bind(ret.node_id);
  //profile->nodes_id = ret.nodes;
  dbo::ptr<Profiles> profilePtr = session_.add(std::move(profile));
  session_.flush();
  transaction.commit();
  id_ = profilePtr.id();
  return id_;
}

void ProfileDbManager::remove(int profile_id) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Profiles> profile =
      session_.find<Profiles>().where("id = ?").bind(profile_id);
  if (!profile) {
    return;
  }
  profile.remove();
  transaction.commit();
}

void ProfileDbManager::update(const Profile &ret) {
  dbo::Transaction transaction(session_);

  dbo::ptr<Profiles> prof =
      session_.find<Profiles>().where("id = ?").bind(ret.id);
  if (!prof) {
    return;
  }
  prof.modify()->node =
      session_.find<Nodes>().where("id = ?").bind(ret.node_id);
  prof.modify()->user =
      session_.find<Users>().where("id = ?").bind(ret.owner_id);
  //prof.modify()->nodes_id = ret.nodes;

  transaction.commit();
}

const Profile &ProfileDbManager::get(int profile_id) {
  dbo::Transaction transaction(session_);

  Profile ret;
  dbo::ptr<Profiles> profile =
      session_.find<Profiles>().where("id = ?").bind(profile_id);
  if (!profile) {
    return ret;
  }
  ret.owner_id = profile->user.id();
  ret.node_id = profile->node.id();
// for (int i = 0; i < ret.nodes.size(); ++i) {
//     profile->nodes_id = ret.nodes[i];
//   }
  //ret.nodes = profile->nodes_id;

  transaction.commit();

  return ret;
}
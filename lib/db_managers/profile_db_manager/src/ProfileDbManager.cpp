#include "ProfileDbManager.hpp"

#include <memory>
#include <sstream>
#include <vector>

#include "DbModels.hpp"
#include "Profile.hpp"

int ProfileDbManager::add(ProfileSptr profile) {
  Wt::Dbo::Transaction transaction(session_);
  std::string nodes_id;
  std::stringstream ss;
  std::unique_ptr<db::Profile> db_profile_unique =
      std::make_unique<db::Profile>();
  db_profile_unique->node_id =
      session_.find<db::Node>().where("id = ?").bind(profile->node_id);
  db_profile_unique->owner_id =
      session_.find<db::User>().where("id = ?").bind(profile->owner_id);

  db::ProfilePtr db_profile = session_.add(std::move(db_profile_unique));
  session_.flush();

  transaction.commit();

  id_ = db_profile.id();
  return id_;
}

void ProfileDbManager::remove(int profile_id) {
  Wt::Dbo::Transaction transaction(session_);

  db::ProfilePtr db_profile =
      session_.find<db::Profile>().where("id = ?").bind(profile_id);

  if (!db_profile) {
    return;
  }

  db_profile.remove();

  transaction.commit();
}

void ProfileDbManager::update(ProfileSptr profile) {
  Wt::Dbo::Transaction transaction(session_);

  db::ProfilePtr db_profile =
      session_.find<db::Profile>().where("id = ?").bind(profile->id);

  if (!db_profile) {
    return;
  }

  db_profile.modify()->node_id =
      session_.find<db::Node>().where("id = ?").bind(profile->node_id);

  db_profile.modify()->owner_id =
      session_.find<db::User>().where("id = ?").bind(profile->owner_id);

  transaction.commit();
}

ProfileSptr ProfileDbManager::get(int profile_id) {
  db::ProfilePtr db_profile =
      session_.find<db::Profile>().where("id = ?").bind(profile_id);

  if (!db_profile) {
    return nullptr;
  }

  ProfileSptr profile = std::make_shared<Profile>();
  profile->node_id = db_profile->node_id.id();
  profile->owner_id = db_profile->owner_id.id();

  return profile;
}

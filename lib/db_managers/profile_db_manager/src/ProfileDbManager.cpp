#include "ProfileDbManager.hpp"

#include "DbModels.hpp"
#include "Profile.hpp"
#include "Session.hpp"

ProfileDbManager::ProfileDbManager(Session& session)
    : session_(session) {
}

int ProfileDbManager::add(ProfileSptr) {
  // TODO
  
  return -1;
}

void ProfileDbManager::remove(int) {
  // TODO
}

void ProfileDbManager::update(ProfileSptr) {
  // TODO
}

ProfileSptr ProfileDbManager::get(int) {
  // TODO

  return std::make_shared<Profile>();
}

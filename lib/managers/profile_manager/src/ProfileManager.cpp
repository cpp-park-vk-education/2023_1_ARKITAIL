#include <memory>

#include "IProfileManager.hpp"
#include "Profile.hpp"
#include "ProfileManager.hpp"
#include "IDbManagers.hpp"

ProfileManager::ProfileManager(std::shared_ptr<IDbManagers> db) :
	db_(db) {}

ProfileSptr ProfileManager::get(int profile_id) {
	return db_->profile_dbm()->get(profile_id);
}

int ProfileManager::add(ProfileSptr profile) {
	return db_->profile_dbm()->add(profile);
}

void ProfileManager::update(ProfileSptr profile) {
	db_->profile_dbm()->update(profile);
}

void ProfileManager::remove(int profile_id) {
	db_->profile_dbm()->remove(profile_id);
}


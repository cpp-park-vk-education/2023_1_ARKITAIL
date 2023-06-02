#include <memory>
#include <vector>

#include "DbMock.hpp"
#include "ProfileDbManagerMock.hpp"
#include "Profile.hpp"

ProfileDbManagerMock::ProfileDbManagerMock(std::shared_ptr<DbMock> db) : 
	db_(db),
	aid_(db->profiles.size()) {}

ProfileSptr ProfileDbManagerMock::get(int profile_id) {
	for (auto e = db_->profiles.begin() + 1; e != db_->profiles.end(); e++)
		if (e->id == profile_id)
			return std::make_shared<Profile>(*e);
	
	return std::make_shared<Profile>(db_->profiles[0]);
}

int ProfileDbManagerMock::add(ProfileSptr profile) {
	db_->profiles.emplace_back(
		aid_,
		profile->node_id,
		profile->owner_id,
		profile->nodes,
		profile->name
	);

	return aid_++;
}

void ProfileDbManagerMock::update(ProfileSptr profile) {
	for (auto e = db_->profiles.begin() + 1; e != db_->profiles.end(); e++)
		if (e->id == profile->id) {
			e->node_id = profile->node_id;
			e->owner_id = profile->owner_id;
			e->nodes = profile->nodes;
			e->name = profile->name;
			break;
		};
}

void ProfileDbManagerMock::remove(int profile_id) {
	for (auto e = db_->profiles.begin() + 1; e != db_->profiles.end(); e++)
		if (e->id == profile_id) {
			db_->profiles.erase(e);
			break;
		}
}


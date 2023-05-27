#include <vector>

#include "ProfileDbManagerMock.hpp"
#include "Profile.hpp"

ProfileDbManagerMock::ProfileDbManagerMock() : 
	data_(),
	aid_(1) {

	data_.emplace_back(0, 0, 0, std::vector<int>());
}

ProfileSptr ProfileDbManagerMock::get(int profile_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == profile_id)
			return std::make_shared<Profile>(*e);
	
	return std::make_shared<Profile>(data_[0]);
}

int ProfileDbManagerMock::add(ProfileSptr profile) {
	data_.emplace_back(
		aid_,
		profile->node_id,
		profile->owner_id,
		profile->nodes
	);

	return aid_++;
}

void ProfileDbManagerMock::update(ProfileSptr profile) {
	for (auto e : data_)
		if (e.id == profile->id)
			e = *profile;
}

void ProfileDbManagerMock::remove(int profile_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == profile_id)
			data_.erase(e);
}


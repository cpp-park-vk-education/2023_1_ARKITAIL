#include <vector>

#include "ProfileDbManagerMock.hpp"
#include "Profile.hpp"

ProfileDbManagerMock::ProfileDbManagerMock() : 
	data_(),
	aid_(1) {

	data_.emplace_back(0, 0, 0, std::vector<int>());
}

const Profile& ProfileDbManagerMock::get(int profile_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == profile_id)
			return *e;
	
	return data_[0];
}

int ProfileDbManagerMock::add(const Profile& profile) {
	data_.emplace_back(
		aid_,
		profile.node_id,
		profile.owner_id,
		profile.nodes
	);

	return aid_++;
}

void ProfileDbManagerMock::update(const Profile& profile) {
	for (auto e : data_)
		if (e.id == profile.id)
			e = profile;
}

void ProfileDbManagerMock::remove(int profile_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == profile_id)
			data_.erase(e);
}


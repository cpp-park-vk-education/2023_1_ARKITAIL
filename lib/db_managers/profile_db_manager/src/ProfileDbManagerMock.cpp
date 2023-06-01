#include <vector>

#include "ProfileDbManagerMock.hpp"
#include "Profile.hpp"

ProfileDbManagerMock::ProfileDbManagerMock() : 
data_(),
aid_(1) {

	// data_.emplace_back(0, 0, 0, std::vector<size_t>(), "");
}

const Profile& ProfileDbManagerMock::get(size_t profile_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == profile_id)
			return *e;
	
	return data_[0];
}

size_t ProfileDbManagerMock::add(const Profile& profile) {
	data_.emplace_back(
		aid_,
		profile.node_id,
		profile.owner_id,
		profile.nodes,
		profile.name
	);

	return aid_++;
}

void ProfileDbManagerMock::remove(size_t profile_id) {
	for (auto e = data_.begin() + 1; e != data_.end(); e++)
		if (e->id == profile_id)
			data_.erase(e);
}


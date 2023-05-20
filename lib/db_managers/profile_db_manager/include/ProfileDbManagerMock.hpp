#pragma once

#include <vector>

#include "IProfileDbManager.hpp"
#include "Profile.hpp"

class ProfileDbManagerMock : public IProfileDbManager {
public:
	ProfileDbManagerMock();

	const Profile& get(size_t profile_id);
	size_t add(const Profile& profile);
	void update(const Profile& profile);
	void remove(size_t profile_id);

private:
	std::vector<Profile> data_;
	size_t aid_;

};


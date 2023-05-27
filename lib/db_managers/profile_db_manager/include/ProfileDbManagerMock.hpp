#pragma once

#include <vector>

#include "IProfileDbManager.hpp"
#include "Profile.hpp"

class ProfileDbManagerMock : public IProfileDbManager {
public:
	ProfileDbManagerMock();

	ProfileSptr get(int profile_id);
	int add(ProfileSptr profile);
	void update(ProfileSptr profile);
	void remove(int profile_id);

private:
	std::vector<Profile> data_;
	int aid_;

};


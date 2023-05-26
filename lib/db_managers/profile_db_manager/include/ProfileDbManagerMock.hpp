#pragma once

#include <vector>

#include "IProfileDbManager.hpp"
#include "Profile.hpp"

class ProfileDbManagerMock : public IProfileDbManager {
public:
	ProfileDbManagerMock();

	const Profile& get(int profile_id);
	int add(const Profile& profile);
	void update(const Profile& profile);
	void remove(int profile_id);

private:
	std::vector<Profile> data_;
	int aid_;

};


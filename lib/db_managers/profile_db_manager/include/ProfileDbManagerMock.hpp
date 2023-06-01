#pragma once

#include <vector>

#include "IProfileDbManager.hpp"
#include "Profile.hpp"

class ProfileDbManagerMock : public IProfileDbManager {
public:
	ProfileDbManagerMock();

	ProfileSptr get(size_t profile_id) override;
	size_t add(ProfileSptr profile) override;
	void update(ProfileSptr profile) override;
	void remove(size_t profile_id) override;

private:
	std::vector<Profile> data_;
	size_t aid_;

};


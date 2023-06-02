#pragma once

#include <memory>

#include "IDbManagers.hpp"
#include "IProfileManager.hpp"
#include "Profile.hpp"

class ProfileManager : public IProfileManager {
public:
	explicit ProfileManager(std::shared_ptr<IDbManagers> db);

	ProfileSptr get(int profile_id) override;
	int add(ProfileSptr profile) override;
	void update(ProfileSptr profile) override;
	void remove(int profile_id) override;

private:
	std::shared_ptr<IDbManagers> db_;

};



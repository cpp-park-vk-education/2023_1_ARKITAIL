#pragma once

#include <memory>

#include "IDbManagers.hpp"
#include "IProfileManager.hpp"
#include "Profile.hpp"

class ProfileManager : public IProfileManager {
public:
	ProfileManager(std::shared_ptr<IDbManagers> db);

	ProfileSptr get(size_t profile_id) override;
	size_t add(ProfileSptr profile, size_t directory_id) override;
	void update(ProfileSptr profile) override;
	void remove(size_t profile_id) override;

private:
	std::shared_ptr<IDbManagers> db_;

};



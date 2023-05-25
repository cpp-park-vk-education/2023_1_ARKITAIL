#pragma once

#include <memory>

#include "IDbManagers.hpp"
#include "IProfileManager.hpp"

class ProfileManager : public IProfileManager {
public:
	ProfileManager(std::shared_ptr<IDbManagers> db);

	Profile get(size_t profile_id);
	size_t add(const Profile& profile);
	void remove(size_t profile_id);

private:
	std::shared_ptr<IDbManagers> db_;

};



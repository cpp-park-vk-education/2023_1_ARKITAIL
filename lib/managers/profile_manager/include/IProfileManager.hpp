#pragma once

#include <memory>

#include "Profile.hpp"
#include "Profile.hpp"

class IProfileManager {
public:
	virtual ProfileSptr get(int profile_id) = 0;
	virtual int add(ProfileSptr profile, int directory_id) = 0;
	virtual void update(ProfileSptr profile) = 0;
	virtual void remove(int profile_id) = 0;

};


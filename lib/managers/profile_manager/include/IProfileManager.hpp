#pragma once

#include <memory>

#include "Profile.hpp"
#include "Profile.hpp"

class IProfileManager {
public:
	virtual ProfileSptr get(size_t profile_id) = 0;
	virtual size_t add(ProfileSptr profile, size_t directory_id) = 0;
	virtual void update(ProfileSptr profile) = 0;
	virtual void remove(size_t profile_id) = 0;

};


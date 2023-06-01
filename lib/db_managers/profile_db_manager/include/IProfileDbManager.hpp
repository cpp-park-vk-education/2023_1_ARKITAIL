#pragma once

#include "Profile.hpp"

class IProfileDbManager {
public:
	virtual ProfileSptr get(size_t profile_id) = 0;
	virtual size_t add(ProfileSptr profile) = 0;
	virtual void update(ProfileSptr profile) = 0;
	virtual void remove(size_t profile_id) = 0;

};


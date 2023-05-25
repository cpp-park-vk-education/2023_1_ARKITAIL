#pragma once

#include "Profile.hpp"

class IProfileDbManager {
public:
	virtual const Profile& get(size_t profile_id) = 0;
	virtual size_t add(const Profile& profile) = 0;
	virtual void remove(size_t profile_id) = 0;

};


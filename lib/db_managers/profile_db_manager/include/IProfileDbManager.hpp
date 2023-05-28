#pragma once

#include "Profile.hpp"

class IProfileDbManager {
public:
	virtual ProfileSptr get(int profile_id) = 0;
	virtual int add(ProfileSptr profile) = 0;
	virtual void update(ProfileSptr profile) = 0;
	virtual void remove(int profile_id) = 0;

};


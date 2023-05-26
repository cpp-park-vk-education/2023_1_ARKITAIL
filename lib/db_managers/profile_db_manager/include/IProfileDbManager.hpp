#pragma once

#include "Profile.hpp"

class IProfileDbManager {
public:
	virtual const Profile& get(int profile_id) = 0;
	virtual int add(const Profile& profile) = 0;
	virtual void update(const Profile& profile) = 0;
	virtual void remove(int profile_id) = 0;

};


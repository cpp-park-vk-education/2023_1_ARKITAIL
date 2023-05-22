#pragma once

#include "User.hpp"

class IUserManager {
public:
	virtual const User& get() = 0;
	virtual const User& get(int) = 0;

};


#pragma once

#include "User.hpp"

class IUserManager {
public:
	virtual UserSptr get() = 0;
	virtual UserSptr get(int) = 0;

};


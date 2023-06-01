#pragma once

#include "User.hpp"

class IUserManager {
public:
	virtual UserSptr get() = 0;
	virtual UserSptr get(int user_id) = 0;

};


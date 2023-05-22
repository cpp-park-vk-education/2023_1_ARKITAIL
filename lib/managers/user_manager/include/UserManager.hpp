#pragma once

#include <memory>

#include "IDbManagers.hpp"
#include "IUserManager.hpp"
#include "User.hpp"

class UserManager : public IUserManager {
public:
	UserManager(std::shared_ptr<IDbManagers> db);
	
    const User& get();
    const User& get(int user_id);

private:
	std::shared_ptr<IDbManagers> db_;

};


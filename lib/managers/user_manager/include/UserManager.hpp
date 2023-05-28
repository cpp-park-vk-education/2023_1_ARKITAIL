#pragma once

#include <memory>

#include "IDbManagers.hpp"
#include "IUserManager.hpp"
#include "User.hpp"

class UserManager : public IUserManager {
public:
	UserManager(std::shared_ptr<IDbManagers> db);
	
    UserSptr get() override;
    UserSptr get(int user_id) override;

private:
	std::shared_ptr<IDbManagers> db_;

};


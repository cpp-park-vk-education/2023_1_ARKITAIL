#pragma once

#include "UnmetDeps.hpp"
#include "IUserManager.hpp"
#include "User.hpp"

class UserManager : public IUserManager {
public:
    const User& get();
    const User& get(size_t user_id);

private:
    IUserDbManager* manager_;
    
};


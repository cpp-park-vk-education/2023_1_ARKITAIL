#pragma once

#include <memory>

#include "IDbManagers.hpp"
#include "IUserManager.hpp"
#include "User.hpp"

class UserManagerStub : public IUserManager {
  public:
    UserManagerStub(std::vector<User> users);

    const User& get();
    const User& get(size_t user_id);

  private:
    std::vector<User> users_;
};

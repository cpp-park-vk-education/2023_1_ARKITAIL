#pragma once

#include <memory>

#include "IDbManagers.hpp"
#include "IUserManager.hpp"
#include "User.hpp"

class UserManagerStub : public IUserManager {
  public:
    UserManagerStub(std::vector<User> users);

    UserSptr get() override;
    UserSptr get(int user_id) override;

  private:
    std::vector<User> users_;
};

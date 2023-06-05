#pragma once

#include "DbModels.hpp"
#include "IUserDbManager.hpp"
#include "Session.hpp"

class UserDbManager: public IUserDbManager {
public:
  explicit UserDbManager(Session& session);

  UserSptr get() override;
  UserSptr get(int user_id) override;

private:
  Session& session_;

};


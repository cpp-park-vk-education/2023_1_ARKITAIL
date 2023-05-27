#pragma once

#include "DbModels.hpp"
#include "IUserDbManager.hpp"

class UserDbManager: public IUserDbManager {
public:
  UserDbManager(Wt::Dbo::Session &session) : session_(session) {}

  UserSptr get() override;
  UserSptr get(int user_id) override;

private:
  int id_;
  Wt::Dbo::Session &session_;
};

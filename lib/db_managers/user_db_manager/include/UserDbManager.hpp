#pragma once

#include "mainModel.hpp"
#include "IUserDbManager.hpp"

class UserDbManager: public IUserDbManager {
public:
  UserDbManager(dbo::Session &session) : session_(session) {}

    const User& get(int user_id);

private:
  int id_;
  dbo::Session &session_;
};

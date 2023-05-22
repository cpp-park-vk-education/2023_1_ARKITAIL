#pragma once

#include "mainModel.hpp"

struct RetUser{
  int user_id;
    std::string login;
    std::string email;
    std::string nickname;
    std::string description;
};

class UserManager {
public:
  UserManager(dbo::Session &session) : session_(session) {}

    RetUser Get(int id);

private:
  int id_;
  dbo::Session &session_;
};

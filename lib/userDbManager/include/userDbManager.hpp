#pragma once

#include "mainModel.hpp"

struct Ret_User{
    std::string login;
    std::string email;
    std::string nickname;
    std::string description;
};

class UserManager {
public:
    Ret_User get(const int id);

private:
  int id;
  dbo::Session &session_;
};

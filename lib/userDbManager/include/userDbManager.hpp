#pragma once

#include "mainModel.hpp"

class UserManager {
public:
    users addUser(users);
    users deleteUser(int id);
    users updateUser(users);
    users getByLogin(std::string login);
    bool authenticate(dbo::Auth::Identity& Identity);
    void logout();
};

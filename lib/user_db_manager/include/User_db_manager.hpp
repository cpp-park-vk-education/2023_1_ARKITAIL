#pragma once

#include "Main_model.hpp"

class user_manager {
public:
    users addUser(users);
    users deleteUser(int id);
    users upgradeUser(users);
    users getByLogin(std::string login);
    bool authenticate(dbo::Auth::Identity& Identity);
    void logout();
};

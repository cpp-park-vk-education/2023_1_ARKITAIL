#pragma once

#include "User_db_model.hpp"

class user_manager {
public:
    users addUser(users);
    users deleteUser(int id);
    users upgradeUser(users);
    users getByLogin(std::string login);
    bool authenticate(Wt::Auth::Identity& Identity);
    void logout();
};

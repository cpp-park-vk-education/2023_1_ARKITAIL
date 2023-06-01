#pragma once

#include "User.hpp"

class IUserDbManager {
public:
    virtual UserSptr get() = 0; // вернуть текущего пользователя
    virtual UserSptr get(int user_id) = 0;

};


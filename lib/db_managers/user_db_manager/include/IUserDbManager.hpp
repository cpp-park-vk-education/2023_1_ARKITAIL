#pragma once

#include "User.hpp"

class IUserDbManager {
public:
    virtual const User& get() = 0;
    virtual const User& get(int user_id) = 0;

};


#pragma once

#include "User.hpp"

class IUserDbManager {
public:
    virtual const User& get() = 0;
    virtual const User& get(size_t user_id) = 0;

};


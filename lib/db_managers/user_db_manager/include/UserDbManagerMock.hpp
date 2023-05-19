#pragma once

#include "IUserDbManager.hpp"
#include "User.hpp"
#include <vector>

class UserDbManagerMock : public IUserDbManager {
public:
    UserDbManagerMock();

    const User& get() override;
    const User& get(size_t user_id) override;

private:
    std::vector<User> data_;

};


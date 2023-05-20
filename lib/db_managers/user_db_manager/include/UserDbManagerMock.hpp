#pragma once

#include <vector>
#include <memory>

#include "DbMock.hpp"
#include "IUserDbManager.hpp"
#include "User.hpp"

class UserDbManagerMock : public IUserDbManager {
public:
    UserDbManagerMock(std::shared_ptr<DbMock> db);

    const User& get() override;
    const User& get(size_t user_id) override;

private:
    std::shared_ptr<DbMock> db_;

};


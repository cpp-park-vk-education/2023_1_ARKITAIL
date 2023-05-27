#pragma once

#include <vector>
#include <memory>

#include "DbMock.hpp"
#include "IUserDbManager.hpp"
#include "User.hpp"

class UserDbManagerMock : public IUserDbManager {
public:
    UserDbManagerMock(std::shared_ptr<DbMock> db);

    UserSptr get() override;
    UserSptr get(int user_id) override;

private:
    std::shared_ptr<DbMock> db_;

};


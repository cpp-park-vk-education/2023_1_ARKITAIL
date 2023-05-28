#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "CalendarDbManagerMock.hpp"
#include "CalendarManager.hpp"
#include "CommentDbManagerMock.hpp"
#include "DbManagers.hpp"
#include "DbMock.hpp"
#include "DirectoryDbManagerMock.hpp"
#include "DirectoryManager.hpp"
#include "EventDbManagerMock.hpp"
#include "EventManager.hpp"
#include "Managers.hpp"
#include "NodeDbManagerMock.hpp"
#include "NodeManager.hpp"
#include "ProfileDbManagerMock.hpp"
#include "ProfileManager.hpp"
#include "TagDbManagerMock.hpp"
#include "User.hpp"
#include "UserDbManagerMock.hpp"
#include "UserManager.hpp"

class ManagersSuit : public ::testing::Test {
  protected:
    void SetUp() override {
        db = std::make_shared<DbMock>();

        db_managers = std::make_shared<DbManagers>(
            std::make_unique<UserDbManagerMock>(db), std::make_unique<NodeDbManagerMock>(db),
            std::make_unique<DirectoryDbManagerMock>(db),
            std::make_unique<CalendarDbManagerMock>(db), std::make_unique<EventDbManagerMock>(db),
            std::make_unique<CommentDbManagerMock>(), std::make_unique<TagDbManagerMock>(),
            std::make_unique<ProfileDbManagerMock>());

        managers = std::make_unique<Managers>(std::make_unique<UserManager>(db_managers),
                                              std::make_unique<NodeManager>(db_managers),
                                              std::make_unique<DirectoryManager>(db_managers),
                                              std::make_unique<CalendarManager>(db_managers),
                                              std::make_unique<EventManager>(db_managers),
                                              std::make_unique<ProfileManager>(db_managers));
    }

    void TearDown() override {}

    std::shared_ptr<DbMock> db;
    std::shared_ptr<IDbManagers> db_managers;
    std::unique_ptr<IManagers> managers;
};

// Больше проверка моков нежели менеджеров пользователья,
// так как пока данный прользователь просто зарегестрирован
TEST_F(ManagersSuit, GetCurrentUser) {
    User expected = {0, 1, "uma_op", "bannikovtop@gmail.com", "UmaOp", "Arkitail"};

	auto got = managers->user_manager()->get();
	
	EXPECT_EQ(expected.id, got->id);
	EXPECT_EQ(expected.root_id, got->root_id);
	EXPECT_EQ(expected.login, got->login);
	EXPECT_EQ(expected.email, got->email);
	EXPECT_EQ(expected.nickname, got->nickname);
	EXPECT_EQ(expected.description, got->description);
}

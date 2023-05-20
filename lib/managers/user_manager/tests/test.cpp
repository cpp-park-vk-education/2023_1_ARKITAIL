#include <gtest/gtest.h>
#include <memory>

#include "CalendarDbManagerMock.hpp"
#include "CommentDbManagerMock.hpp"
#include "DirectoryDbManagerMock.hpp"
#include "EventDbManagerMock.hpp"
#include "NodeDbManagerMock.hpp"
#include "ProfileDbManagerMock.hpp"
#include "TagDbManagerMock.hpp"
#include "User.hpp"
#include "DbMock.hpp"
#include "DbManagers.hpp"
#include "IManagers.hpp"
#include "UserDbManagerMock.hpp"

class DbSuit : public ::testing::Test {
protected:
	void SetUp() override {
		std::shared_ptr<DbMock> db = std::make_shared<DbMock>();
		db_managers = std::make_shared<DbManagers>(
			std::make_unique<UserDbManagerMock>(db),
			std::make_unique<NodeDbManagerMock>(db),
			std::make_unique<DirectoryDbManagerMock>(db),
			std::make_unique<CalendarDbManagerMock>(db),
			std::make_unique<EventDbManagerMock>(db),
			std::make_unique<CommentDbManagerMock>(),
			std::make_unique<TagDbManagerMock>(),
			std::make_unique<ProfileDbManagerMock>()
		);
	}

	void TearDown() override {}

	std::shared_ptr<DbMock> db;
	std::shared_ptr<IDbManagers> db_managers;
	std::shared_ptr<IManagers> managers;

};

TEST_F(DbSuit, ManagerGetCurrentUser) {
	User expected = {
		0,
		1,
		"uma_op",
		"bannikovtop@gmail.com",
		"UmaOp",
		"Arkitail"
	};

	auto got = managers->user_manager()->get();
	
	EXPECT_EQ(expected.id, got.id);
	EXPECT_EQ(expected.root_id, got.root_id);
	EXPECT_EQ(expected.login, got.login);
	EXPECT_EQ(expected.email, got.email);
	EXPECT_EQ(expected.nickname, got.nickname);
	EXPECT_EQ(expected.description, got.description);
}


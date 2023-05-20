#include <gtest/gtest.h>
#include <memory>

#include "User.hpp"
#include "DbMock.hpp"
#include "IDbManagers.hpp"
#include "IManagers.hpp"

class DbSuit : public ::testing::Test {
protected:
	void SetUp() override {
		std::shared_ptr<DbMock> db = std::make_shared<DbMock>();
		db_managers = std::make_shared<IDbManagers>();
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


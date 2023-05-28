#include "UserDbManagerMock.hpp"

#include "DbMock.hpp"
#include "User.hpp"

UserDbManagerMock::UserDbManagerMock(std::shared_ptr<DbMock> db) :
	db_(db) {}

UserSptr UserDbManagerMock::get() {
	return std::make_shared<User>(db_->users[0]);
}

UserSptr UserDbManagerMock::get(int user_id) {
	return std::make_shared<User>(db_->users[user_id]);
}


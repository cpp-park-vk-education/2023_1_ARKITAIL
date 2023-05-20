#include "UserDbManagerMock.hpp"
#include "DbMock.hpp"

UserDbManagerMock::UserDbManagerMock(std::shared_ptr<DbMock> db) :
	db_(db) {}

const User& UserDbManagerMock::get() {
	return db_->users[0];
}

const User& UserDbManagerMock::get(size_t user_id) {
	return db_->users[user_id];
}


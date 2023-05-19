#include "UserDbManagerMock.hpp"

UserDbManagerMock::UserDbManagerMock() :
	data_() {

	data_.emplace_back(0, 0, "uma_op", "bannikovtop@gmail.com", "UmaOp", "Arkitail");
}

const User& UserDbManagerMock::get() {
	return data_[0];
}

const User& UserDbManagerMock::get(size_t user_id) {
	return data_[user_id];
}


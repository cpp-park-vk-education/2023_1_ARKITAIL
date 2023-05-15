#include "UserManager.hpp"
#include "User.hpp"

const User& UserManager::get() {
	return *(new User());
}

const User& UserManager::get(size_t user_id) {
	return get();
}


#include "UserManager.hpp"
#include "DbManagers.hpp"
#include "User.hpp"

const User& UserManager::get() {
	return DbManagers::instance().user_dbm->get();
}

const User& UserManager::get(size_t user_id) {
	return DbManagers::instance().user_dbm->get(user_id);
}


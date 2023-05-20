#include <memory>

#include "UserManager.hpp"
#include "DbManagers.hpp"
#include "IDbManagers.hpp"
#include "User.hpp"

UserManager::UserManager(std::shared_ptr<IDbManagers> db) :
	db_(db) {}

const User& UserManager::get() {
	return db_->user_dbm()->get();
}

const User& UserManager::get(size_t user_id) {
	return db_->user_dbm()->get(user_id);
}


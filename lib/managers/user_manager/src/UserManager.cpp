#include <memory>

#include "UserManager.hpp"
#include "DbManagers.hpp"
#include "IDbManagers.hpp"
#include "User.hpp"

UserManager::UserManager(std::shared_ptr<IDbManagers> db) :
	db_(db) {}

UserSptr UserManager::get() {
	return db_->user_dbm()->get();
}

UserSptr UserManager::get(int user_id) {
	return db_->user_dbm()->get(user_id);
}


#include "UserDbManager.hpp"

#include <memory>
#include <string>

#include <Wt/Dbo/Transaction.h>

#include "DbModels.hpp"
#include "User.hpp"

UserDbManager::UserDbManager(Session& session)
    : session_(session) {
}

UserSptr UserDbManager::get() {
  Wt::Dbo::Transaction transaction(session_);

  db::UserPtr db_user = session_.user();
  
  if (!db_user) {
    Wt::log("UserDbManger::get(): the user is not logged in"); 
    return std::make_shared<User>();
  }

  User user {
    db_user.id(),
    db_user->root_id,
    db_user->login,
    db_user->email,
    db_user->nickname,
    db_user->description
  };
  
  transaction.commit();

  return std::make_shared<User>(std::move(user));
}

UserSptr UserDbManager::get(long long user_id) {
  Wt::Dbo::Transaction transaction(session_);
  
  db::UserPtr db_user
      = session_.find<db::User>().where("id = ?").bind(user_id);

  if (!db_user) {
    Wt::log("UserDbManger::get(long long user_id): not found user witd id = "
        + std::to_string(user_id));
    return std::make_shared<User>();
  }

  User user {
    db_user.id(),
    db_user->root_id,
    db_user->login,
    db_user->email,
    db_user->nickname,
    db_user->description
  };

  transaction.commit();

  return std::make_shared<User>(std::move(user));
}

#include "UserDbManager.hpp"

#include <Wt/Dbo/Transaction.h>
#include <memory>
#include <string>

#include <Wt/Auth/Identity.h>
#include <Wt/Auth/Login.h>
#include <Wt/Auth/User.h>

#include "DbModels.hpp"
#include "SessionScopeMap.hpp"
#include "User.hpp"

UserSptr UserDbManager::get() {
  Wt::log("UserDbManger::get()");
  
  Session* session = SessionScopeMap::instance().get()->session();
  db::UserPtr db_user = session->user();

  if (!db_user) {
    Wt::log("UserDbManger::get(): the user is not logged in"); 
    return std::make_shared<User>();
  }

  Wt::Dbo::Transaction transaction(*session);
  
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

UserSptr UserDbManager::get(int user_id) {
  Wt::log("UserDbManger::get(int user_id): " + std::to_string(user_id));
  // Wt::Dbo::ptr<db::User> db_user
  //     = session_.find<db::User>().where("id = ?").bind(user_id);

  // User user;
  // user.id = user_id;
  // // user.root_id = ???
  // user.email = db_user->email;
  // user.login = db_user->login;
  // user.nickname = db_user->nickname;
  // user.description = db_user->description;

  // return std::make_shared<User>(std::move(user));
  //

  return std::make_shared<User>();
}

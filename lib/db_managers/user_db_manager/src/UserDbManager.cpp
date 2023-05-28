#include "UserDbManager.hpp"

UserSptr UserDbManager::get() {
  // TODO(affeeal)
  return nullptr;
}

UserSptr UserDbManager::get(int user_id) {
  Wt::Dbo::ptr<db::User> db_user
      = session_.find<db::User>().where("id = ?").bind(user_id);

  User user;
  user.id = user_id;
  // user.root_id = ???
  user.email = db_user->email;
  user.login = db_user->login;
  user.nickname = db_user->nickname;
  user.description = db_user->description;

  return std::make_shared<User>(std::move(user));
}

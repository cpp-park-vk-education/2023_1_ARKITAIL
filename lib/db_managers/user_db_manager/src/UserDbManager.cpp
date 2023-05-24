#include "UserDbManager.hpp"

const User& UserDbManager::get(int user_id) {
  dbo::Transaction transaction(session_);

  User ret;
  dbo::ptr<Users> user =
      session_.find<Users>().where("id = ?").bind(user_id);
  ret.email = user->email;
  ret.login = user->login;
  ret.nickname = user->nickname;
  ret.description = user->description;

  transaction.commit();
  return ret;
}
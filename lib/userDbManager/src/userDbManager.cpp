#include "userDbManager.hpp"

Ret_User UserManager::get(const int id) {
  dbo::Transaction transaction(session_);

  Ret_User ret;
  dbo::ptr<users> user =
      session_.find<users>().where("id = ?").bind(id);
  ret.email = user->email;
  ret.login = user->login;
  ret.nickname = user->nickname;
  ret.description = user->description;

  transaction.commit();
  return ret;
}
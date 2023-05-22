#include "userDbManager.hpp"

RetUser UserManager::Get(int id) {
  dbo::Transaction transaction(session_);

  RetUser ret;
  dbo::ptr<Users> user =
      session_.find<Users>().where("id = ?").bind(id);
  ret.email = user->email;
  ret.login = user->login;
  ret.nickname = user->nickname;
  ret.description = user->description;

  transaction.commit();
  return ret;
}
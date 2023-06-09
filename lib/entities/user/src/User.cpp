#include "User.hpp"

User::User(
    int id,
    int root_id,
    std::string login,
    std::string email,
    std::string nickname,
    std::string description)
  : id(id),
    root_id(root_id),
    login(login),
    email(email),
    nickname(nickname),
    description(description) {
}

bool User::operator==(const User& a) const {
  return std::tie(id, root_id, login, email, nickname, description) ==
           std::tie(a.id, a.root_id, a.login, a.email, a.nickname, a.description);
}

#pragma once

#include <memory>
#include <string>

class User;
using UserSptr = std::shared_ptr<User>;

class User {
 public:
  User() = default;
  User(
    long long id,
    int root_id,
    std::string login,
    std::string email,
    std::string nickname,
    std::string description);

  long long id;
  int root_id;

  std::string login;
  std::string email;
  std::string nickname;
  std::string description;
};

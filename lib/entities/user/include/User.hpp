#pragma once

#include <memory>
#include <string>

class User;
using UserSptr = std::shared_ptr<User>;

class User {
 public:
  User() = default;
  User(
    int id,
    int root_id,
    std::string login,
    std::string email,
    std::string nickname,
    std::string description);

  int id;
  int root_id;

  std::string login;
  std::string email;
  std::string nickname;
  std::string description;
};

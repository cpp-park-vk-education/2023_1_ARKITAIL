#pragma once

#include <cstddef>
#include <string>

class User {
 public:
  User() = default;
  User(
    size_t id,
    size_t root_id,
    std::string login,
    std::string email,
    std::string nickname,
    std::string description);
  
  // getter'ы
  size_t id() const;
  size_t root_id() const;

  const std::string& login() const;
  const std::string& email() const;
  const std::string& nickname() const;
  const std::string& description() const;

  // setter'ы
  void set_id(size_t id);
  void set_root_id(size_t root_id);

  void set_login(const std::string& login);
  void set_email(const std::string& email);
  void set_nickname(const std::string& nickname);
  void set_description(const std::string& description);
 private:
  size_t id_;
  size_t root_id_;

  std::string login_;
  std::string email_;
  std::string nickname_;
  std::string description_;
};

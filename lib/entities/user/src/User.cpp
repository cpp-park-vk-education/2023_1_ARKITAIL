#include "User.hpp"

#include <cstddef>

User::User(
    size_t id,
    size_t root_id,
    std::string login,
    std::string email,
    std::string nickname,
    std::string description)
  : id_(id),
    root_id_(root_id),
    login_(login),
    email_(email),
    nickname_(nickname),
    description_(description) {
}

// getter'ы

size_t User::id() const {
  return id_;
}

size_t User::root_id() const {
  return root_id_;
}

const std::string& User::login() const {
  return login_;
}

const std::string& User::email() const {
  return email_;
}

const std::string& User::nickname() const {
  return nickname_;
}

const std::string& User::description() const {
  return description_;
}

// setter'ы

void User::set_id(size_t id) {
  id_ = id;
}

void User::set_root_id(size_t root_id) {
  root_id_ = root_id;
}

void User::set_login(const std::string& login) {
  login_ = login;
}

void User::set_email(const std::string& email) {
  email_ = email;
}

void User::set_nickname(const std::string& nickname) {
  nickname_ = nickname;
}

void User::set_description(const std::string& description) {
  description_ = description;
}

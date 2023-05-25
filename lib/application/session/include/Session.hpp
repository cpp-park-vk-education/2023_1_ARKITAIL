#pragma once

#include <Wt/Auth/AbstractUserDatabase.h>
#include <Wt/Auth/AuthService.h>
#include <Wt/Auth/Login.h>
#include <Wt/Auth/Dbo/UserDatabase.h>
#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>
#include <Wt/WGlobal.h>

#include <memory>

#include "User.hpp"

using UserDatabase = Wt::Auth::Dbo::UserDatabase<AuthInfo>;

class Session : public Wt::Dbo::Session {
 public:
  static void ConfigureAuth();
  
  Session(const std::string& connection_information);

  Wt::Dbo::ptr<User> GetUser() const;

  Wt::Auth::AbstractUserDatabase& users();
  Wt::Auth::Login& login();

  static const Wt::Auth::AuthService& GetAuthService();
  static const Wt::Auth::PasswordService& GetPasswordService();
 private:
  std::unique_ptr<UserDatabase> users_;
  Wt::Auth::Login login_;
};

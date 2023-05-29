#pragma once

#include <Wt/Auth/PasswordService.h>
#include <Wt/WGlobal.h>
#include <Wt/Auth/AbstractUserDatabase.h>
#include <Wt/Auth/AuthService.h>
#include <Wt/Auth/Dbo/UserDatabase.h>
#include <Wt/Auth/Login.h>
#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>

#include <memory>

#include "DbModels.hpp"

using UserDatabase = Wt::Auth::Dbo::UserDatabase<db::AuthInfo>;

class Session : public Wt::Dbo::Session {
 public:
  static void ConfigureAuth();
  
  static const Wt::Auth::AuthService& auth_service();
  static const Wt::Auth::PasswordService& password_service();

  Session();
  explicit Session(const std::string& connection_information);

  db::UserPtr user() const;
  Wt::Auth::AbstractUserDatabase& users();
  Wt::Auth::Login& login();

 private:
  static Wt::Auth::AuthService auth_service_;
  static Wt::Auth::PasswordService password_service_;

  std::unique_ptr<UserDatabase> users_;
  Wt::Auth::Login login_;

};

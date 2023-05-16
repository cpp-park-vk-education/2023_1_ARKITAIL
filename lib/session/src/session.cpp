#include "session.hpp"

#include <Wt/Auth/AuthService.h>
#include <Wt/Auth/HashFunction.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Auth/PasswordStrengthValidator.h>
#include <Wt/Auth/PasswordVerifier.h>
#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/Dbo/backend/Postgres.h>

#include <exception>
#include <memory>

#include "user.hpp"

namespace {
  Wt::Auth::AuthService auth_service;
  Wt::Auth::PasswordService password_service(auth_service);
};

void Session::ConfigureAuth() {
  auth_service.setAuthTokensEnabled(true, "logincookie");
  // TODO: подтверждение по email:
  // auth_service.setEmailVerificationEnabled(true);
  // auth_service.setEmailVerificationRequired(true);
  
  auto verifier = std::make_unique<Wt::Auth::PasswordVerifier>();
  verifier->addHashFunction(std::make_unique<Wt::Auth::BCryptHashFunction>(7));

  password_service.setVerifier(std::move(verifier));
  password_service.setAttemptThrottlingEnabled(true);
  password_service.setStrengthValidator(
      std::make_unique<Wt::Auth::PasswordStrengthValidator>());
}

Session::Session(const std::string& conn_info) {
  auto connection = std::make_unique<Wt::Dbo::backend::Postgres>(conn_info);
  connection->setProperty("show-queries", "true");

  setConnection(std::move(connection));

  mapClass<User>("user");
  mapClass<AuthInfo>("auth_info");
  mapClass<AuthInfo::AuthIdentityType>("auth_identity");
  mapClass<AuthInfo::AuthTokenType>("auth_token");

  try {
    createTables();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  users_ = std::make_unique<UserDatabase>(*this);
}

Wt::Auth::AbstractUserDatabase& Session::users() {
  return *users_;
}

Wt::Auth::Login& Session::login() {
  return login_;
}

Wt::Dbo::ptr<User> Session::GetUser() const {
  if (login_.loggedIn()) {
    auto auth_info = users_->find(login_.user());
    return auth_info->user();
  } else {
    return Wt::Dbo::ptr<User>();
  }
}

const Wt::Auth::AuthService& Session::GetAuthService() {
  return auth_service;
}

const Wt::Auth::PasswordService& Session::GetPasswordService() {
  return password_service;
}

#include "Session.hpp"

#include <exception>
#include <memory>

#include <Wt/Auth/AuthService.h>
#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/Auth/HashFunction.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Auth/PasswordStrengthValidator.h>
#include <Wt/Auth/PasswordVerifier.h>
#include <Wt/Dbo/backend/Postgres.h>

#include "DbModels.hpp"
#include "Utils.hpp"

Wt::Auth::AuthService Session::auth_service_ { };
Wt::Auth::PasswordService Session::password_service_ { Session::auth_service_ };

void Session::ConfigureAuth() {
  auth_service_.setAuthTokensEnabled(true, "logincookie");
  // TODO(affeeal): подтверждение по email:
  // auth_service.setEmailVerificationEnabled(true);
  // auth_service.setEmailVerificationRequired(true);
  
  auto verifier = std::make_unique<Wt::Auth::PasswordVerifier>();
  verifier->addHashFunction(std::make_unique<Wt::Auth::BCryptHashFunction>(7));

  password_service_.setVerifier(std::move(verifier));
  password_service_.setAttemptThrottlingEnabled(true);
  password_service_.setStrengthValidator(
      std::make_unique<Wt::Auth::PasswordStrengthValidator>());
}

const Wt::Auth::AuthService& Session::auth_service() {
  return auth_service_;
}

const Wt::Auth::PasswordService& Session::password_service() {
  return password_service_;
}

Session::Session()
    : Session(GetConnectionInformation()) {
}

Session::Session(const std::string& conn_info) {
  auto connection = std::make_unique<Wt::Dbo::backend::Postgres>(conn_info);
  connection->setProperty("show-queries", "true");

  setConnection(std::move(connection));

  mapClass<db::Calendar>("calendar");
  mapClass<db::Comment>("comment");
  mapClass<db::Directory>("directory");
  mapClass<db::Event>("event");
  mapClass<db::Node>("node");
  mapClass<db::Profile>("profile");
  mapClass<db::Tag>("tag");
  mapClass<db::User>("user");

  mapClass<db::AuthInfo>("auth_info");
  mapClass<db::AuthInfo::AuthIdentityType>("auth_identity");
  mapClass<db::AuthInfo::AuthTokenType>("auth_token");

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

db::UserPtr Session::user() const {
  if (login_.loggedIn()) {
    auto auth_info = users_->find(login_.user());
    return auth_info->user();
  } else {
    return db::UserPtr();
  }
}


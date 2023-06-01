#include "Session.hpp"

#include <exception>
#include <memory>

#include <Wt/WLogger.h>
#include <Wt/Auth/AuthService.h>
#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/Auth/HashFunction.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Auth/PasswordStrengthValidator.h>
#include <Wt/Auth/PasswordVerifier.h>
#include <Wt/Dbo/Transaction.h>
#include <Wt/Dbo/backend/Postgres.h>

#include "DbModels.hpp"
#include "Node.hpp"
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

  mapClass<db::AuthInfo>("auth_info");
  mapClass<db::AuthInfo::AuthIdentityType>("auth_identity");
  mapClass<db::AuthInfo::AuthTokenType>("auth_token");
  mapClass<db::Calendar>("calendar");
  mapClass<db::Comment>("comment");
  mapClass<db::Directory>("directory");
  mapClass<db::Event>("event");
  mapClass<db::Node>("node");
  mapClass<db::Profile>("profile");
  mapClass<db::Tag>("tag");
  mapClass<db::User>("user");

  Wt::Dbo::Transaction transaction(*this);
  
  try {
    createTables();
    Wt::log("Using existing database");
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  transaction.commit();

  users_ = std::make_unique<UserDatabase>(*this);
}

Wt::Auth::AbstractUserDatabase& Session::users() {
  return *users_;
}

Wt::Auth::Login& Session::login() {
  return login_;
}

db::UserPtr Session::user() {
  if (login_.loggedIn()) {
    Wt::Dbo::ptr<db::AuthInfo> auth_info = users_->find(login_.user());
    db::UserPtr db_user = auth_info->user();

    // Если для auth_info не существует соответствующего пользователя,
    // создаём его.
    if (!db_user) {
      Wt::Dbo::Transaction transaction(*this);
      
      db_user = add(std::make_unique<db::User>());
      auth_info.modify()->setUser(db_user);

      // создание нод
      db::NodePtr root = add(std::make_unique<db::Node>());

      db::NodePtr private_group = add(std::make_unique<db::Node>());
      db::NodePtr public_group = add(std::make_unique<db::Node>());
      db::NodePtr subscriptions_group = add(std::make_unique<db::Node>());
      db::NodePtr profiles_group = add(std::make_unique<db::Node>());

      db::DirectoryPtr root_directory
          = add(std::make_unique<db::Directory>());
      db::DirectoryPtr public_directory
          = add(std::make_unique<db::Directory>());
      db::DirectoryPtr private_directory
          = add(std::make_unique<db::Directory>());
      db::DirectoryPtr subscribtions_directory
          = add(std::make_unique<db::Directory>());
      db::DirectoryPtr profile_directory
          = add(std::make_unique<db::Directory>());
      
      flush();
      
      // корневая директория
      root_directory.modify()->owner = db_user;
      root_directory.modify()->node = root;
      root_directory.modify()->name = "Корень";
      root_directory.modify()->description = "Корень";
      
      // приватная директория
      private_directory.modify()->owner = db_user;
      private_directory.modify()->node = private_group;
      private_directory.modify()->name = "Приватные календари";
      private_directory.modify()->description = "Приватные календари";
      
      // публичная директория
      public_directory.modify()->owner = db_user;
      public_directory.modify()->node = public_group;
      public_directory.modify()->name = "Публичные календари";
      public_directory.modify()->description = "Публичные календари";
      
      // директория подписок
      subscribtions_directory.modify()->owner = db_user;
      subscribtions_directory.modify()->node = subscriptions_group;
      subscribtions_directory.modify()->name = "Подписки";
      subscribtions_directory.modify()->description = "Подписки";
      
      // директория профилей
      profile_directory.modify()->owner = db_user;
      profile_directory.modify()->node = profiles_group;
      profile_directory.modify()->name = "Профили";
      profile_directory.modify()->description = "Профили";
      
      // корень
      root.modify()->parent = nullptr;
      root.modify()->resource_id = static_cast<int>(root_directory.id());
      root.modify()->owner = db_user;
      root.modify()->type = NodeType::ROOT;

      db_user.modify()->root = root;

      // приватная группа
      private_group.modify()->parent = root;
      private_group.modify()->resource_id
          = static_cast<int>(private_group.id());
      private_group.modify()->owner = db_user;
      private_group.modify()->type = NodeType::PRIVATE_GROUP;
      
      // публичная группа
      public_group.modify()->parent = root;
      public_group.modify()->resource_id
          = static_cast<int>(public_group.id());
      public_group.modify()->owner = db_user;
      public_group.modify()->type = NodeType::PUBLIC_GROUP;
      
      // группа подписок
      subscriptions_group.modify()->parent = root;
      subscriptions_group.modify()->resource_id
          = static_cast<int>(subscriptions_group.id());
      subscriptions_group.modify()->owner = db_user;
      subscriptions_group.modify()->type = NodeType::SUBSCRIPTIONS_GROUP;
      
      // группа профилей
      profiles_group.modify()->parent = root;
      profiles_group.modify()->resource_id
          = static_cast<int>(profiles_group.id());
      profiles_group.modify()->owner = db_user;
      profiles_group.modify()->type = NodeType::PROFILE_GROUP;

      transaction.commit();
    }
    
    return db_user;
  } else {
    return db::UserPtr();
  }
}


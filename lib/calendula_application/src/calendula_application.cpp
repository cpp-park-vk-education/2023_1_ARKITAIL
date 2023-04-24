#include "calendula_application.hpp"

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WGlobal.h>

#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/Identity.h>
#include <Wt/Auth/PasswordService.h>
            
#include <memory>

#include "session.hpp"
#include "utils.hpp"

CalendulaApplication::CalendulaApplication(const Wt::WEnvironment& env)
  : Wt::WApplication(env),
    session_(GetConnectionInformation()) {
  session_.GetLogin().changed().connect(this, &CalendulaApplication::AuthEvent);
  
  // TODO: разобраться со стилями
  // root()->addStyleClass("container");
  // setTheme(std::make_shared<Wt::WBootstrap5Theme>());

  auto auth_widget = std::make_unique<Wt::Auth::AuthWidget>(
      Session::GetAuthService(), session_.GetUsers(), session_.GetLogin());
  auth_widget->model()->addPasswordAuth(&Session::GetPasswordService());
  auth_widget->setRegistrationEnabled(true);
  auth_widget->processEnvironment();

  root()->addWidget(std::move(auth_widget));
}

void CalendulaApplication::AuthEvent() {
  if (session_.GetLogin().loggedIn()) {
    auto user = session_.GetLogin().user();
    log("notice")
      << "User " << user.id()
      << " (" << user.identity(Wt::Auth::Identity::LoginName) << ")"
      << "logged in.";
  } else {
    log("notice") << "User logged out.";
  }
}

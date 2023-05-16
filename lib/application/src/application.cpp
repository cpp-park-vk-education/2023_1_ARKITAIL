#include "application.hpp"

#include <Wt/WApplication.h>
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WGlobal.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/Identity.h>
#include <Wt/Auth/PasswordService.h>
            
#include <iostream>
#include <memory>

#include "calendar.hpp"
#include "session.hpp"
#include "utils.hpp"
#include "calendar_create_dialog.hpp"
#include "calendar_edit_dialog.hpp"

Application::Application(const Wt::WEnvironment& env)
  : Wt::WApplication(env),
    session_(GetConnectionInformation()) {
  session_.login().changed().connect(this, &Application::AuthEvent);
  
  root()->addStyleClass("container");
  setTheme(std::make_shared<Wt::WBootstrap5Theme>());

  messageResourceBundle().use(appRoot() + "data/templates");

  // Временный блок для демонстрации работы диалогов
  auto calendar_create = std::make_unique<Wt::WPushButton>("Создать календарь");
  calendar_create->clicked().connect([=]{
      CreateCalendarDialog::Show(root());
  });
  root()->addWidget(std::move(calendar_create));

  auto calendar = Calendar {
    "Название календаря",
    "Описание календаря",
    "Приватный",
    "#D12828",
  };
  auto calendar_edit = std::make_unique<Wt::WPushButton>("Редактировать календарь");
  calendar_edit->clicked().connect([=]{
      EditCalendarDialog::Show(root(), std::make_shared<Calendar>(calendar));
  });
  root()->addWidget(std::move(calendar_edit));

  auto auth_widget = std::make_unique<Wt::Auth::AuthWidget>(
      Session::GetAuthService(), session_.users(), session_.login());
  auth_widget->model()->addPasswordAuth(&Session::GetPasswordService());
  auth_widget->setRegistrationEnabled(true);
  auth_widget->processEnvironment();

  // Раскомментировать в production'е
  // root()->addWidget(std::move(auth_widget));
}

void Application::AuthEvent() {
  if (session_.login().loggedIn()) {
    auto user = session_.login().user();
    log("notice")
      << "User " << user.id()
      << " (" << user.identity(Wt::Auth::Identity::LoginName) << ")"
      << "logged in.";
  } else {
    log("notice") << "User logged out.";
  }
}

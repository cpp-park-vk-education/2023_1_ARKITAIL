#include "application.hpp"

#include <Wt/WApplication.h>
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WGlobal.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/Identity.h>
#include <Wt/Auth/PasswordService.h>
            
#include <memory>

#include "calendar.hpp"
#include "calendar_create_dialog.hpp"
#include "calendar_edit_dialog.hpp"
#include "event.hpp"
#include "event_dialog.hpp"
#include "session.hpp"
#include "utils.hpp"

Application::Application(const Wt::WEnvironment& env)
  : Wt::WApplication(env),
    session_(GetConnectionInformation()) {
  session_.login().changed().connect(this, &Application::AuthEvent);
  
  root()->addStyleClass("container");
  setTheme(std::make_shared<Wt::WBootstrap5Theme>());

  messageResourceBundle().use(appRoot() + "data/templates");

  // Временный блок для демонстрации работы диалогов

  // Диалог создания календаря
  auto calendar_create = std::make_unique<Wt::WPushButton>("Создать календарь");
  calendar_create->clicked().connect([=]{
      CreateCalendarDialog::Show(root());
  });
  root()->addWidget(std::move(calendar_create));

  root()->addWidget(std::make_unique<Wt::WBreak>());

  // Диалог редактирования календаря
  auto calendar = Calendar {
    "Название календаря",
    "Описание календаря",
    "Приватный",
    "#D12828",
  };
  auto calendar_edit = std::make_unique<Wt::WPushButton>("Редактировать календарь");
  calendar_edit->clicked().connect([=]{
      EditCalendarDialog::Show(
          root(),
          std::make_shared<Calendar>(calendar));
  });
  root()->addWidget(std::move(calendar_edit));

  root()->addWidget(std::make_unique<Wt::WBreak>());

  // Заглушки для диалогов событий
  std::vector<std::shared_ptr<Calendar>> public_calendars;
  for (auto i = 0; i < 3; i++) {
    Calendar calendar {
      "Публичный календарь " + std::to_string(i), "...", "...", "..." };
    public_calendars.push_back(std::make_shared<Calendar>(calendar));
  }

  std::vector<std::shared_ptr<Calendar>> private_calendars;
  for (auto i = 0; i < 3; i++) {
    Calendar calendar {
      "Приватный календарь " + std::to_string(i), "...", "...", "..." };
    private_calendars.push_back(std::make_shared<Calendar>(calendar));
  }
  
  // Диалог создания события
  auto event_create = std::make_unique<Wt::WPushButton>("Создать событие");
  event_create->clicked().connect([=]{
      EventDialog::Show(
          root(),
          public_calendars,
          private_calendars);
  });
  root()->addWidget(std::move(event_create));

  root()->addWidget(std::make_unique<Wt::WBreak>());

  // Диалог редактирования события
  Event event = {
    "Название события",
    "Описания события",
    "Приватный календарь 1",
    "16.05.2023",
    "18:00:00",
    "16.05.2023",
    "18:30:00",
    "Ежедневно",
    "31.05.2023",
  };
  auto event_edit = std::make_unique<Wt::WPushButton>("Редактировать событие");
  event_edit->clicked().connect([=]{
      EventDialog::Show(
          root(),
          public_calendars,
          private_calendars,
          std::make_shared<Event>(event));
  });
  root()->addWidget(std::move(event_edit));

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
    // TODO(affeeal): загрузка страниц
  } else {
    // TODO(affeeal): выгрузка страниц
  }
}

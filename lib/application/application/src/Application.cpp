#include "Application.hpp"

#include <Wt/WBootstrap5Theme.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WGlobal.h>
#include <Wt/WWidget.h>
#include <Wt/Auth/AuthWidget.h>

#include <string>
#include <thread>

#include "MainP.hpp"
#include "OtherP.hpp"
#include "SessionScopeMap.hpp"
#include "navbar_w.hpp"
#include "Deferred.hpp"

Application::Application(const Wt::WEnvironment& env) :
    Wt::WApplication(env),
    pages_(),
    cur_swap_(),
    cur_page_(nullptr) {

    setTitle("Calendula");
    setTheme(std::make_unique<Wt::WBootstrap5Theme>());
    useStyleSheet("/static/style.css");
    messageResourceBundle().use(appRoot() + "data/templates");

    navbar_ = root()->addWidget(std::make_unique<NavbarW>());

    // Some initial widgets configuration
    pages_.emplace("/calendars", std::make_unique<Deferred<MainP, Wt::WContainerWidget>>())
        .first->second.set_destination(&cur_swap_);
    navbar_->addLink("Calendars", "/calendars");

    pages_.emplace("/profile", std::make_unique<Deferred<OtherP, Wt::WContainerWidget>>())
        .first->second.set_destination(&cur_swap_);
    navbar_->addLink("My Profile", "/profile");

    pages_.emplace("/search", std::make_unique<Deferred<Wt::WContainerWidget>>())
        .first->second.set_destination(&cur_swap_);
    navbar_->addLink("Search", "/search");

    // Main page configuration
    pages_["/search"].build_destination();
    cur_swap_.swap();
    cur_page_ = root()->addWidget(cur_swap_.get_content()->get());

    internalPathChanged().connect(this, &Application::route);

    // Connections mediator connections establishing
    
    // root()->addWidget(CreateAuthWiget());
}

void Application::route(const std::string& internalPath) {
    cur_swap_.get_content()->set(root()->removeWidget(cur_page_));
    cur_swap_.swap();
    pages_[internalPath].build_destination();
    cur_swap_.swap();
    cur_page_ = root()->addWidget(cur_swap_.get_content()->get());
}

std::unique_ptr<Wt::Auth::AuthWidget> Application::CreateAuthWiget() {
  Session* session = SessionScopeMap::instance().get()->session();
  std::unique_ptr<Wt::Auth::AuthWidget> auth_widget
      = std::make_unique<Wt::Auth::AuthWidget>(
          session->auth_service(),
          session->users(),
          session->login());
  auth_widget->model()->addPasswordAuth(&session->password_service());
  auth_widget->setRegistrationEnabled(true);
  auth_widget->processEnvironment();
  return auth_widget;
}

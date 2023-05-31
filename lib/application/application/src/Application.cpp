#include "Application.hpp"

#include <Wt/WBootstrap5Theme.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WWidget.h>

#include <string>
#include <thread>

#include "MainP.hpp"
#include "OtherP.hpp"
#include "OtherUserP.hpp"
#include "SearchPage.hpp"
#include "SessionScopeMap.hpp"
#include "navbar_w.hpp"

#include "Deferred.hpp"

Application::Application(const Wt::WEnvironment& env) :
    Wt::WApplication(env),
    session_(),
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
    pages_.emplace("/profile", std::make_unique<Deferred<OtherUserP, Wt::WContainerWidget>>()) // заменить на UserP
        .first->second.set_destination(&cur_swap_);
    navbar_->addLink("My Profile", "/profile");
    pages_.emplace("/search", std::make_unique<Deferred<SearchP, Wt::WContainerWidget>>())
        .first->second.set_destination(&cur_swap_);
    navbar_->addLink("Search", "/search");

    pages_.emplace("/other_calendar", std::make_unique<Deferred<OtherP, Wt::WContainerWidget>>())
        .first->second.set_destination(&cur_swap_);

    pages_.emplace("/other_profile", std::make_unique<Deferred<OtherUserP, Wt::WContainerWidget>>())
        .first->second.set_destination(&cur_swap_);

    // Main page configuration
    pages_["/search"].build_destination();
    cur_swap_.swap();
    cur_page_ = root()->addWidget(cur_swap_.get_content()->get());

    internalPathChanged().connect(this, &Application::route);

    // Connections mediator connections establishing
}

void Application::route(const std::string& internalPath) {
    cur_swap_.get_content()->set(root()->removeWidget(cur_page_));
    cur_swap_.swap();
    pages_[internalPath].build_destination();
    cur_swap_.swap();
    cur_page_ = root()->addWidget(cur_swap_.get_content()->get());
}

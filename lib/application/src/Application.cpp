#include "Application.hpp"

#include <Wt/WBootstrap5Theme.h>
#include <Wt/WText.h>
#include <Wt/WWidget.h>

#include <string>

#include "ConnectionsMediator.hpp"
#include "PageWidget.hpp"
#include "main_p.hpp"
#include "navbar_w.hpp"
#include "other_p.hpp"

Application::Application(const Wt::WEnvironment& env)
    : Wt::WApplication(env), session_(), pages_(), cur_swap_(), cur_page_(nullptr) {
    setTitle("Calendula");
    setTheme(std::make_unique<Wt::WBootstrap5Theme>());
    useStyleSheet("/static/style.css");

    navbar_ = root()->addWidget(std::make_unique<NavbarW>());
    // Some initial widgets configuration
    pages_.emplace("/calendars", std::make_unique<MainP>()).first->second.set_destination(&cur_swap_);
    navbar_->addLink("Calendars", "/calendars");
    pages_.emplace("/profile", std::make_unique<OtherP>()).first->second.set_destination(&cur_swap_);
    navbar_->addLink("My Profile", "/profile");
    pages_.emplace("/search", std::make_unique<PageWidget>()).first->second.set_destination(&cur_swap_);
    navbar_->addLink("Search", "/search");

    // Main page configuration
    pages_["/calendars"].build_destination();
    cur_swap_.swap();
    cur_page_ = root()->addWidget(cur_swap_.get_content());

    internalPathChanged().connect(this, &Application::route);

    // Connections mediator connections establishing
    ConnectionsMediator::instance().connect();
}

void Application::route(const std::string& internalPath) {
    cur_swap_.set_content(root()->removeWidget(cur_page_));
    cur_swap_.swap();
    pages_[internalPath].build_destination();
    cur_swap_.swap();
    cur_page_ = root()->addWidget(cur_swap_.get_content());

}

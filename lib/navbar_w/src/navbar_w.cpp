#include "navbar_w.hpp"

NavbarW::NavbarW() {
    navigation = addNew<Wt::WNavigationBar>();
    navigation->setTitle("Calendula", "/");

    contents_stack = addNew<Wt::WStackedWidget>();
    auto leftMenu = std::make_unique<Wt::WMenu>(contents_stack);
    left_menu_ = navigation->addMenu(std::move(leftMenu));

    calendar = addLink("Calendars", "/calendars");

    profile = addLink("My Profile", "/profile");

    search = addLink("Search", "/search");

    auto exitPtr = std::make_unique<Wt::WPushButton>("Logout");
    exit = exitPtr.get();
    navigation->addWidget(std::move(exitPtr));

    addSignals();
    addStyle();
}

Wt::WMenuItem *NavbarW::addLink(const std::string &iconPath, const std::string &path) {
    auto tmp = left_menu_->addItem(iconPath);
    tmp->setLink(Wt::WLink(Wt::LinkType::InternalPath, path));
    return tmp;
}

void NavbarW::addProfile(std::unique_ptr<Wt::WWidget> content) { profile->setContents(std::move(content)); }

void NavbarW::addCalendar(std::unique_ptr<Wt::WWidget> content) { calendar->setContents(std::move(content)); }

void NavbarW::addSearch(std::unique_ptr<Wt::WWidget> content) { search->setContents(std::move(content)); }

void NavbarW::addSignals() { exit->clicked().connect(this, &NavbarW::logout); }

void NavbarW::addStyle() {
    setStyleClass("top-0");
    navigation->setResponsive(true);
    navigation->addStyleClass("navbar navbar-light bg-light navbar-expand-lg");
    contents_stack->addStyleClass("contents");
    left_menu_->addStyleClass("me-auto");
    exit->addStyleClass("ms-2");
}

void NavbarW::logout() {
    // выходим
}

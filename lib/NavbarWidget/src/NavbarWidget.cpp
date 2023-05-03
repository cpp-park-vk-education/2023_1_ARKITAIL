#include "NavbarWidget.hpp"

NavbarWidget::NavbarWidget() {
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

Wt::WMenuItem *NavbarWidget::addLink(const std::string &iconPath, const std::string &path) {
    auto tmp = left_menu_->addItem(iconPath);
    tmp->setLink(Wt::WLink(Wt::LinkType::InternalPath, path));
    return tmp;
}

void NavbarWidget::addProfile(std::unique_ptr<Wt::WWidget> content) { profile->setContents(std::move(content)); }

void NavbarWidget::addCalendar(std::unique_ptr<Wt::WWidget> content) { calendar->setContents(std::move(content)); }

void NavbarWidget::addSearch(std::unique_ptr<Wt::WWidget> content) { search->setContents(std::move(content)); }

void NavbarWidget::addSignals() { exit->clicked().connect(this, &NavbarWidget::logout); }

void NavbarWidget::addStyle() {
    setStyleClass("top-0");
    navigation->setResponsive(true);
    navigation->addStyleClass("navbar navbar-light bg-light navbar-expand-lg");
    contents_stack->addStyleClass("contents");
    left_menu_->addStyleClass("me-auto");
    exit->addStyleClass("ms-2");
}

void NavbarWidget::logout() {
    // выходим
}

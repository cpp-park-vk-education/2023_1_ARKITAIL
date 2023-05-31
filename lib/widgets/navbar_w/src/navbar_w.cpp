#include "navbar_w.hpp"
#include "SessionScopeMap.hpp"

#include <Wt/Auth/Login.h>
#include <iostream>

#include <Wt/WMenu.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WPushButton.h>

NavbarW::NavbarW() {
    setTitle("Calendula", "/");

    left_menu_ = addMenu(std::make_unique<Wt::WMenu>());

    exit_button_ = addWidget(std::make_unique<Wt::WPushButton>("Logout"));

    addSignals();
    addStyle();
}

Wt::WMenuItem *NavbarW::addLink(const std::string &icon_path, const std::string &path) {
    auto tmp = left_menu_->addItem(icon_path);
    tmp->setLink(Wt::WLink(Wt::LinkType::InternalPath, path));
    return tmp;
}

void NavbarW::addSignals() {
    exit_button_->clicked().connect(this, &NavbarW::logout);
}

void NavbarW::addStyle() {
    setStyleClass("top-0");
    setResponsive(true);
    addStyleClass("navbar navbar-light bg-light navbar-expand-lg");
    left_menu_->addStyleClass("me-auto");
}

void NavbarW::logout() {
  auto& login = SessionScopeMap::instance().get()->session()->login();
  std::cout << (login.state() == Wt::Auth::LoginState::LoggedOut) << std::endl;
  login.logout();
  std::cout << (login.state() == Wt::Auth::LoginState::LoggedOut) << std::endl;
}

#pragma once

#include <Wt/WMenu.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WPushButton.h>

class NavbarW : public Wt::WNavigationBar {
  public:
    NavbarW();
    ~NavbarW() = default;

    Wt::WMenuItem *addLink(const std::string &icon_path, const std::string &path);

  private:
    Wt::WMenu *left_menu_;
    Wt::WPushButton *exit_button_;

    void addSignals();
    void addStyle();
    void logout();
};
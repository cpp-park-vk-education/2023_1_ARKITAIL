#pragma once

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WMenu.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPushButton.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WString.h>
#include <Wt/WText.h>

#include <memory>

class NavbarWidget : public Wt::WContainerWidget {
  public:
    NavbarWidget();
    ~NavbarWidget() = default;

    void addProfile(std::unique_ptr<Wt::WWidget> content);
    void addCalendar(std::unique_ptr<Wt::WWidget> content);
    void addSearch(std::unique_ptr<Wt::WWidget> content);

  private:
    Wt::WNavigationBar *navigation;
    Wt::WStackedWidget *contents_stack;
    Wt::WMenu *left_menu_;
    Wt::WMenuItem *profile;
    Wt::WMenuItem *calendar;
    Wt::WMenuItem *search;
    Wt::WPushButton *exit;

    Wt::WMenuItem *addLink(const std::string &iconPath, const std::string &path);
    void addSignals();
    void addStyle();
    void logout();
};
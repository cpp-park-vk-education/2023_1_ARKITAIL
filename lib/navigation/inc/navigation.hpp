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

class Navigation : public Wt::WContainerWidget {
  public:
    Navigation();
    ~Navigation() = default;

    void addProfile(std::unique_ptr<Wt::WWidget> content);
    void addPrivateCalendar(std::unique_ptr<Wt::WWidget> content);
    void addPublicCalendar(std::unique_ptr<Wt::WWidget> content);
    void addProfiles(std::unique_ptr<Wt::WWidget> content);

  private:
    Wt::WNavigationBar *navigation;
    Wt::WStackedWidget *contents_stack;
    Wt::WMenu *left_menu_;
    Wt::WMenuItem *profile;
    Wt::WMenuItem *private_calendar;
    Wt::WMenuItem *public_calendar;
    Wt::WMenuItem *profiles;
    Wt::WText *searchResult_;  // убрать
    Wt::WWidget *searchProf_;  // убрать
    Wt::WLineEdit *search_line;
    Wt::WPushButton *exit;

    Wt::WMenuItem *addLink(const std::string &iconPath, const std::string &path);
    void addSignals();
    void addStyle();
    void logout();
    void search();
};
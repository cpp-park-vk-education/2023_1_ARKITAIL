#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WMenu.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WPushButton.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WText.h>
#include <Wt/WTree.h>

#include "calendar.hpp"
#include "tree.hpp"

class PublicCalendar : public Wt::WContainerWidget {
  public:
    PublicCalendar();
    ~PublicCalendar() = default;

  private:
    Calendar* calendar;
    Tree* tree;
};
#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WMenu.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WPushButton.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WText.h>
#include <Wt/WTree.h>

class Tree : public Wt::WContainerWidget {
  public:
    Tree();
    ~Tree() = default;

  private:
    Wt::WLineEdit *search;
    Wt::WTree *tree;
};
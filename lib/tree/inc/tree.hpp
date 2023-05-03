#pragma once

#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WMenu.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WPushButton.h>
#include <Wt/WSignal.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WText.h>
#include <Wt/WTree.h>

class Tree : public Wt::WContainerWidget {
  public:
    Tree();
    ~Tree() = default;
    Wt::Signal<int> m_signal;

  private:
    Wt::WLineEdit *search;
    Wt::WTree *tree;
    Wt::WCheckBox *check;
};
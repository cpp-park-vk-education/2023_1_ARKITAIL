#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPushButton.h>

class OptionsW : public Wt::WPopupMenu {
  public:
    OptionsW();
    ~OptionsW() = default;

    //   void show(Wt::WWidget* button);

    // protected:
    //   Wt::WPopupMenu* popup_;
};

#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPushButton.h>

class OptionsW : public Wt::WContainerWidget {
  public:
    OptionsW();
    ~OptionsW() = default;

  protected:
    Wt::WPopupMenu* popup_;
    Wt::WPushButton* options_button_;
};

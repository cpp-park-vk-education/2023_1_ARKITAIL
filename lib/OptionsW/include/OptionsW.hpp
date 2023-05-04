#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WPopupMenu.h>

class OptionsW : public Wt::WContainerWidget {
  public:
    OptionsW();
    ~OptionsW() = default;

  protected:
    Wt::WPopupMenu* options_button_;
};

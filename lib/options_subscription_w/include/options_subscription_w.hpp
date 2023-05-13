#pragma once

#include <Wt/WMenuItem.h>
#include <Wt/WPopupMenu.h>

class OptionsSubscriptionW : public Wt::WPopupMenu {
  public:
    OptionsSubscriptionW();
    ~OptionsSubscriptionW() = default;

  private:
    Wt::WMenuItem* to_author_button_;
    Wt::WMenuItem* unsubscribe_button_;
};

#pragma once

#include <Wt/WMenuItem.h>
#include <Wt/WPopupMenu.h>

#include "options_w.hpp"

class OptionsSubscriptionW : public OptionsW {
  public:
    OptionsSubscriptionW();
    ~OptionsSubscriptionW() = default;

  private:
    Wt::WMenuItem* unsubscribe_button_;
};

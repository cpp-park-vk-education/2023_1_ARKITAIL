#pragma once

#include <Wt/WMenuItem.h>

#include "OptionsW.hpp"

class OptionsSubscriptionW : public OptionsW {
  public:
    OptionsSubscriptionW();
    ~OptionsSubscriptionW() = default;

  private:
    Wt::WMenuItem* to_author_button_;
    Wt::WMenuItem* unsubscribe_button_;
};

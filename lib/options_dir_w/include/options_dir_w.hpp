#pragma once

#include <Wt/WMenuItem.h>

#include "options_w.hpp"

class OptionsDirW : public OptionsW {
  public:
    OptionsDirW();
    ~OptionsDirW() = default;

  protected:
    Wt::WMenuItem* add_calendar_button_;
    Wt::WMenuItem* move_button_;
};

#pragma once

#include <Wt/WMenuItem.h>

#include "options_dir_w.hpp"
#include "options_w.hpp"

class OptionsCalendarsDirW : public OptionsDirW {
  public:
    OptionsCalendarsDirW();
    ~OptionsCalendarsDirW() = default;

  private:
    Wt::WMenuItem* remove_button_;
};

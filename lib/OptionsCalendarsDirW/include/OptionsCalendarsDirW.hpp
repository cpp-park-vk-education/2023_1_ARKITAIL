#pragma once

#include <Wt/WMenuItem.h>

#include "OptionsW.hpp"

class OptionsCalendarsDirW : public OptionsW {
  public:
    OptionsCalendarsDirW();
    ~OptionsCalendarsDirW() = default;

  private:
    Wt::WMenuItem* add_calendar_button_;
    Wt::WMenuItem* remove_button_;
    Wt::WMenuItem* move_button_;
};

#pragma once
#include <Wt/WMenuItem.h>

#include <memory>

#include "options_w.hpp"

class OptionsPersonalCalendarW : public OptionsW {
  public:
    OptionsPersonalCalendarW();
    ~OptionsPersonalCalendarW() = default;

  private:
    Wt::WMenuItem* remove_button_;
    Wt::WMenuItem* move_button_;
};

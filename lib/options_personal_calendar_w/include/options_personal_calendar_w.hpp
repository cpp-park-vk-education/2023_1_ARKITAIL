#pragma once
#include <Wt/WMenuItem.h>
#include <Wt/WPopupMenu.h>

#include <memory>

class OptionsPersonalCalendarW : public Wt::WPopupMenu {
  public:
    OptionsPersonalCalendarW();
    ~OptionsPersonalCalendarW() = default;

  private:
    Wt::WMenuItem* remove_button_;
    Wt::WMenuItem* move_button_;
};

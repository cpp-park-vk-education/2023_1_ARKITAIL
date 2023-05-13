#pragma once

#include <Wt/WMenuItem.h>
#include <Wt/WPopupMenu.h>

class OptionsCalendarsDirW : public Wt::WPopupMenu {
  public:
    OptionsCalendarsDirW();
    ~OptionsCalendarsDirW() = default;

  private:
    Wt::WMenuItem* add_calendar_button_;
    Wt::WMenuItem* remove_button_;
    Wt::WMenuItem* move_button_;
};

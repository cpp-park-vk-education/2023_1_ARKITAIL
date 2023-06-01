#pragma once

#include <Wt/WPushButton.h>

#include "calendar_header_w.hpp"

class PersonalCalendarHeaderW : public CalendarHeaderW {
  public:
    PersonalCalendarHeaderW();
    ~PersonalCalendarHeaderW() = default;

  private:
    Wt::WPushButton* button_add_event_;

    void addEvent();

    PersonalCalendarHeaderW* addButtons() override;
    PersonalCalendarHeaderW* addConnections() override;
};

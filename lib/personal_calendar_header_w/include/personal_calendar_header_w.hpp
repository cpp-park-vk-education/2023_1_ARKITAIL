#pragma once

#include <Wt/WPushButton.h>

#include "add_event_d.hpp"
#include "calendar_header_w.hpp"

class PersonalCalendarHeaderW : public CalendarHeaderW {
  public:
    PersonalCalendarHeaderW();
    ~PersonalCalendarHeaderW() = default;

  private:
    Wt::WPushButton* button_add_event_;
    AddEventDialog* add_event_dialog_;

    void addEvent();
    void addConnections() override;
};

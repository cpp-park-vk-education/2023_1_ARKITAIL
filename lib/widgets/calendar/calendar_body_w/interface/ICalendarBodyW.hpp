#pragma once

#include <Wt/WDate.h>

#include <vector>

#include "Event.hpp"

class ICalendarBodyW : public Wt::WContainerWidget {
  public:
    virtual ~ICalendarBodyW() = default;
    virtual void update(Wt::WDate begin_date, std::vector<Event> events) = 0;
    virtual void updateCalendar(Wt::WDate begin_date, std::vector<Event> events) = 0;
};

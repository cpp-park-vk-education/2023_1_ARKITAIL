#pragma once

#include <Wt/WDate.h>

#include <CalendarBodyW.hpp>
#include <EventW.hpp>

class WeekW : public CalendarBodyW {
  public:
    WeekW();
    ~WeekW() = default;
    void updateCalendar(Wt::WDate selected_date) override;
};

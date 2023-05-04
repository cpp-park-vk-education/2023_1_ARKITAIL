#pragma once

#include <CalendarBodyW.hpp>

class DayW : public CalendarBodyW {
  public:
    DayW();
    ~DayW() = default;

  private:
    void updateCalendar(Wt::WDate selected_date) override;
};

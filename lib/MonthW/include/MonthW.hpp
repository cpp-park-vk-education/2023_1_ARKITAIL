#pragma once

#include <CalendarBodyW.hpp>

class MonthW : public CalendarBodyW {
  public:
    MonthW();
    ~MonthW() = default;

  private:
    void updateCalendar(Wt::WDate selected_date) override;
};

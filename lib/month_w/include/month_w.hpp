#pragma once

#include <calendar_body_w.hpp>

class MonthW : public CalendarBodyW {
  public:
    MonthW();
    ~MonthW() = default;

  private:
    void updateCalendar(Wt::WDate selected_date) override;
};

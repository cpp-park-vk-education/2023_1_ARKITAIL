#pragma once

#include <calendar_body_w.hpp>

class MonthW : public CalendarBodyW {
  public:
    MonthW();
    ~MonthW() = default;

  private:
    void update(Wt::WDate selected_date) override;
};

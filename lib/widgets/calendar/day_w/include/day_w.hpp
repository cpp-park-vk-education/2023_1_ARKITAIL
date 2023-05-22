#pragma once

#include <calendar_body_w.hpp>

class DayW : public CalendarBodyW {
  public:
    DayW();
    ~DayW() = default;

  private:
    void update(Wt::WDate selected_date) override;
};

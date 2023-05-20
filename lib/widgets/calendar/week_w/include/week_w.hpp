#pragma once

#include <Wt/WDate.h>

#include <calendar_body_w.hpp>
#include <event_w.hpp>

class WeekW : public CalendarBodyW {
  public:
    WeekW();
    ~WeekW() = default;

  private:
    void update(Wt::WDate selected_date) override;
};

#pragma once

#include <Wt/WDate.h>

#include <CalendarBodyW.hpp>
#include <EventW.hpp>

class WeekW : public CalendarBodyW {
  public:
    WeekW();
    ~WeekW() = default;

  private:
    void update(Wt::WDate begin_date, std::vector<Event> events) override;
};

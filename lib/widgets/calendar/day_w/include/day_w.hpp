#pragma once

#include <CalendarBodyW.hpp>

class DayW : public CalendarBodyW {
  public:
    DayW();
    ~DayW() = default;

  private:
    void update(Wt::WDate begin_date, std::vector<Event> events) override;
};

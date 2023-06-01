#pragma once

#include <CalendarBodyW.hpp>

class MonthW : public CalendarBodyW {
  public:
    MonthW();
    ~MonthW() = default;

  private:
    void update(Wt::WDate begin_date, std::vector<Event> events) override;
};

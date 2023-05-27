#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WTable.h>

#include <memory>

#include "ICalendarBodyW.hpp"

class CalendarBodyW : public ICalendarBodyW {
  public:
    CalendarBodyW();
    ~CalendarBodyW() = default;

    void updateCalendar(Wt::WDate begin_date, std::vector<Event> events) override;

  protected:
    Wt::WTable* table_;
    void makeHeaderTime();
    void activateToday(Wt::WDate& selected_date);
};

#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WTable.h>

#include <memory>

class CalendarBodyW : public Wt::WContainerWidget {
  public:
    CalendarBodyW();
    ~CalendarBodyW() = default;
    virtual void updateCalendar(Wt::WDate selected_date) = 0;

  protected:
    Wt::WTable* table_;
    void makeHeaderTime();
    void activateToday(Wt::WDate* selected_date, int begin_week_day, int shift);
};

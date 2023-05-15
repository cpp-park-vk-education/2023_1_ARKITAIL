#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WTable.h>

#include <memory>

class InterfaceCalendarBodyW : public Wt::WContainerWidget {
  public:
    virtual ~InterfaceCalendarBodyW() = default;
    virtual void update(Wt::WDate selected_date) = 0;
    virtual void updateCalendar(Wt::WDate selected_date) = 0;
};

class CalendarBodyW : public InterfaceCalendarBodyW {
  public:
    CalendarBodyW();
    ~CalendarBodyW() = default;

    void updateCalendar(Wt::WDate selected_date);

  protected:
    Wt::WTable* table_;
    void makeHeaderTime();
    void activateToday(Wt::WDate* selected_date, int begin_week_day, int shift);
};

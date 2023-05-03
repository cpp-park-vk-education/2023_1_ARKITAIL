#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WTable.h>

#include <memory>

class CalendarBodyWidget : public Wt::WContainerWidget {
  public:
    CalendarBodyWidget();
    ~CalendarBodyWidget() = default;
    virtual void updateCalendar(std::unique_ptr<Wt::WDate> selected_date) = 0;

  protected:
    Wt::WTable *table_;
    void makeHeaderTime();
    void activateToday(std::unique_ptr<Wt::WDate> selected_date, int begin_week_day, int shift);
};

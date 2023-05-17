#pragma once

class InterfaceCalendarBodyW : public Wt::WContainerWidget {
  public:
    virtual ~InterfaceCalendarBodyW() = default;
    virtual void update(Wt::WDate selected_date) = 0;
    virtual void updateCalendar(Wt::WDate selected_date) = 0;
};

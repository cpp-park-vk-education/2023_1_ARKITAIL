#pragma once

class ICalendarBodyW : public Wt::WContainerWidget {
  public:
    virtual ~ICalendarBodyW() = default;
    virtual void update(Wt::WDate selected_date) = 0;
    virtual void updateCalendar(Wt::WDate selected_date) = 0;
};

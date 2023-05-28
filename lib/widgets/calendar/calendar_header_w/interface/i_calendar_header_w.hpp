#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WString.h>
#include <Wt/WText.h>

#include <memory>

#include "Event.hpp"

enum Range {
    MONTH,
    WEEK,
    DAY
};

class ICalendarHeaderW : public Wt::WContainerWidget {
  public:
    virtual ~ICalendarHeaderW() = default;

    virtual Wt::Signal<Wt::WDate, Wt::WDate>& selectedDateChanged() = 0;
    virtual Wt::Signal<Range>& rangeChanged() = 0;
    virtual void setRange() = 0;
    virtual ICalendarHeaderW* addConnections() = 0;
    virtual ICalendarHeaderW* addButtons() = 0;

    virtual Wt::WString makeTitle() = 0;

    virtual void emitDates() = 0;

  protected:
    virtual void addStyle() = 0;

    virtual void switchToToday() = 0;
    virtual void switchToPrev() = 0;
    virtual void switchToNext() = 0;
};

#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WString.h>
#include <Wt/WText.h>

#include <memory>

enum Range {
    MONTH = 0,
    WEEK,
    DAY
};

class ICalendarHeaderW : public Wt::WContainerWidget {
  public:
    virtual ~ICalendarHeaderW() = default;

    virtual Wt::Signal<Wt::WDate>& selectedDateChanged() = 0;
    virtual Wt::Signal<Range>& rangeChanged() = 0;
    virtual Wt::Signal<>& eventAdded() = 0;
    virtual void setRange() = 0;
    virtual void addConnections() = 0;

  protected:
    virtual Wt::WString makeTitle() = 0;
    virtual void addStyle() = 0;
    virtual void switchToToday() = 0;
    virtual void switchToPrev() = 0;
    virtual void switchToNext() = 0;
};

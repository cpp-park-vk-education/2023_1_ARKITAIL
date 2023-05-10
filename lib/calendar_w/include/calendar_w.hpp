#pragma once

#include <Wt/WContainerWidget.h>

#include <vector>

#include "calendar_body_w.hpp"
#include "calendar_header_w.hpp"
#include "tree_w.hpp"
#include "utils.hpp"

class CalendarW : public Wt::WContainerWidget {
  public:
    CalendarW();
    ~CalendarW() = default;

    void addConnections();
    InterfaceCalendarHeaderW* addHeader(std::unique_ptr<InterfaceCalendarHeaderW> header);
    InterfaceCalendarBodyW* addCalendarBodyDay(std::unique_ptr<InterfaceCalendarBodyW> calendar);
    InterfaceCalendarBodyW* addCalendarBodyMonth(std::unique_ptr<InterfaceCalendarBodyW> calendar);
    InterfaceCalendarBodyW* addCalendarBodyWeek(std::unique_ptr<InterfaceCalendarBodyW> calendar);
    void setHeaderRange();

  private:
    Wt::WContainerWidget* calendar_box_;
    TreeW* tree_;
    InterfaceCalendarHeaderW* header_;
    Range range_;
    std::vector<InterfaceCalendarBodyW*> calendars_;

    void setCalendarRange(Range range);
};

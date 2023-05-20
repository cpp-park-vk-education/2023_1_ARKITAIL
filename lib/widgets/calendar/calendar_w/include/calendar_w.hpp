#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>

#include <vector>

#include "calendar_body_w.hpp"
#include "calendar_header_w.hpp"
#include "tree_w.hpp"

class CalendarW : public Wt::WContainerWidget {
  public:
    CalendarW();
    ~CalendarW() = default;

    void addConnections();
    ICalendarHeaderW* addHeader(std::unique_ptr<ICalendarHeaderW> header);
    ICalendarBodyW* addCalendarBodyDay(std::unique_ptr<ICalendarBodyW> calendar);
    ICalendarBodyW* addCalendarBodyMonth(std::unique_ptr<ICalendarBodyW> calendar);
    ICalendarBodyW* addCalendarBodyWeek(std::unique_ptr<ICalendarBodyW> calendar);
    void setHeaderRange();

  private:
    TreeW* tree_;
    Wt::WPushButton* show_tree_button_;
    Range range_;
    ICalendarHeaderW* header_;
    Wt::WContainerWidget* calendar_box_;
    std::vector<ICalendarBodyW*> calendars_;

    void setCalendarRange(Range range);
    void showTree();
};

#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>

#include <map>
#include <memory>

#include "CalendarBodyW.hpp"
#include "TreeW.hpp"
#include "CalendarHeaderW.hpp"

class CalendarW : public Wt::WContainerWidget {
  public:
    CalendarW();

    void addConnections();
    TreeW* addTree(std::unique_ptr<TreeW> tree);
    ICalendarHeaderW* addHeader(std::unique_ptr<ICalendarHeaderW> header);
    ICalendarBodyW* addCalendarBodyDay(std::unique_ptr<ICalendarBodyW> calendar);
    ICalendarBodyW* addCalendarBodyMonth(std::unique_ptr<ICalendarBodyW> calendar);
    ICalendarBodyW* addCalendarBodyWeek(std::unique_ptr<ICalendarBodyW> calendar);

  private:
    Wt::WHBoxLayout* tree_panel_layout;
    TreeW* tree_;
    Wt::WPushButton* show_tree_button_;
    Range range_;
    ICalendarHeaderW* header_;
    Wt::WContainerWidget* calendar_box_;
    std::map<int, ICalendarBodyW*> calendars_;

    void setCalendarRange(Range range);
    void showTree();
};

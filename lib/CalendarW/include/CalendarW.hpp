#pragma once

#include <Wt/WContainerWidget.h>

#include "CalendarBodyW.hpp"
#include "CalendarHeaderW.hpp"
#include "TreeW.hpp"
#include "utils.hpp"

class CalendarW : public Wt::WContainerWidget {
  public:
    CalendarW();
    ~CalendarW() = default;

  private:
    Wt::WContainerWidget* calendar_box_;
    TreeW* tree_;
    CalendarHeaderW* header_;
    CalendarBodyW* calendar_;

    void addConnections();
    void setCalendarRange(Range range);
};

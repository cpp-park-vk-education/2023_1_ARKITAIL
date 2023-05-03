#pragma once

#include <Wt/WContainerWidget.h>

#include "CalendarBodyWidget.hpp"
#include "CalendarHeaderWidget.hpp"
#include "utils.hpp"

class CalendarWidget : public Wt::WContainerWidget {
  public:
    CalendarWidget();
    ~CalendarWidget() = default;

  private:
    // TreeWidget* tree_;
    CalendarHeaderWidget* header_;
    CalendarBodyWidget* calendar_;

    void addConnections();
    void setCalendarRange(Range range);
};

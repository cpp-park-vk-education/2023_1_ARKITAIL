#pragma once

#include <Wt/WDate.h>

#include <CalendarBodyWidget.hpp>
#include <EventWidget.hpp>

class WeekWidget : public CalendarBodyWidget {
  public:
    WeekWidget();
    ~WeekWidget() = default;
    void updateCalendar(std::unique_ptr<Wt::WDate> selected_date) override;
};

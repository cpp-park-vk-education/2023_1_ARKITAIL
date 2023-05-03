#pragma once

#include <CalendarBodyWidget.hpp>

class DayWidget : public CalendarBodyWidget {
  public:
    DayWidget();
    ~DayWidget() = default;

  private:
    void updateCalendar(std::unique_ptr<Wt::WDate> selected_date) override;
};

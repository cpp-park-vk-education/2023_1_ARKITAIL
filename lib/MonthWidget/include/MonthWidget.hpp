#pragma once

#include <CalendarBodyWidget.hpp>

class MonthWidget : public CalendarBodyWidget {
  public:
    MonthWidget();
    ~MonthWidget() = default;

  private:
    void updateCalendar(std::unique_ptr<Wt::WDate> selected_date) override;
};

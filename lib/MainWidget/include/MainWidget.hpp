#pragma once
#include <Wt/WContainerWidget.h>

#include "CalendarWidget.hpp"

class MainWidget : public Wt::WContainerWidget {
  public:
    MainWidget();
    ~MainWidget() = default;

  private:
    CalendarWidget* calendar_;
};

#pragma once

#include <Wt/WContainerWidget.h>

#include "calendar_w.hpp"

class MainP : public Wt::WContainerWidget {
  public:
    MainP();
    ~MainP() = default;

  private:
    CalendarW* calendar_;
};

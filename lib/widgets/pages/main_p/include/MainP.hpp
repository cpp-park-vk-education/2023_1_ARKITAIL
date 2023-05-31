#pragma once

#include <Wt/WContainerWidget.h>

#include "CalendarW.hpp"

class MainP : public Wt::WContainerWidget {
  public:
    MainP();
    ~MainP() = default;

  private:
    CalendarW* calendar_;
};

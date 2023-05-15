#pragma once

#include <Wt/WContainerWidget.h>

#include "PageWidget.hpp"
#include "calendar_w.hpp"

class MainP : public PageWidget {
  public:
    MainP();
    ~MainP() = default;

  private:
    CalendarW* calendar_;
};

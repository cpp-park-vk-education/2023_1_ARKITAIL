#pragma once

#include <Wt/WContainerWidget.h>

#include "PageWidget.hpp"
#include "calendar_w.hpp"

class OtherP : public PageWidget {
  public:
    OtherP();
    ~OtherP() = default;

  private:
    CalendarW* calendar_;
};

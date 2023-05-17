#pragma once

#include <Wt/WContainerWidget.h>

#include "calendar_w.hpp"

class OtherP : public Wt::WContainerWidget {
  public:
    OtherP();
    ~OtherP() = default;

  private:
    CalendarW* calendar_;
};

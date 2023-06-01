#pragma once

#include <Wt/WContainerWidget.h>

#include "CalendarW.hpp"

class OtherP : public Wt::WContainerWidget {
  public:
    OtherP();
    ~OtherP() = default;

  private:
    CalendarW* calendar_;
};

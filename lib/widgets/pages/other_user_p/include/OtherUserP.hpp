#pragma once

#include <Wt/WContainerWidget.h>

#include "calendar_w.hpp"

class OtherUserP : public Wt::WContainerWidget {
  public:
    OtherUserP();
    ~OtherUserP() = default;

    void init(const User& user);

  private:
    Wt::WText* test_;
};

#pragma once

#include <Wt/WContainerWidget.h>

class UserP : public Wt::WContainerWidget {
  public:
    UserP();
    ~UserP() = default;

    void init(const User& user);

  private:
    Wt::WText* test_;
};

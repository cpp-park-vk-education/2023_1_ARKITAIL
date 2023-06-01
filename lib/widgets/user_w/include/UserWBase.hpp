#pragma once

#include <Wt/WContainerWidget.h>
#include "UserAnchorW.hpp"

class UserWBase : public Wt::WContainerWidget {
  public:
    UserWBase(const User& user);
    ~UserWBase() = default;

  protected:
    Wt::WImage* avatar_;
    Wt::WContainerWidget* nickname_block_;
    Wt::WText* description_;
};

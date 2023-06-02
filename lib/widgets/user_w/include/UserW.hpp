#pragma once

#include "UserWBase.hpp"

class UserW : public UserWBase {
  public:
    UserW(const User& user);
    ~UserW() = default;

  private:
    Wt::WText* nickname_;
};

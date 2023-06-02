#pragma once

#include "UserWBase.hpp"
#include "UserAnchorW.hpp"

class OtherUserW : public UserWBase {
  public:
    OtherUserW(const User& user);
    ~OtherUserW() = default;

  private:
    UserAnchorW* nickname_;
};

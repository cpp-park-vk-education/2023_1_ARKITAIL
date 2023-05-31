#pragma once

#include <Wt/WAnchor.h>

#include "User.hpp"

class UserAnchorW : public Wt::WAnchor {
  public:
    UserAnchorW(const User& tag);
    ~UserAnchorW() = default;

  private:
    Wt::Signal<User> user_clicked_;
    User user_;
    
};

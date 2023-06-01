#pragma once

#include <Wt/WAnchor.h>

#include "User.hpp"
#include "Node.hpp"

class UserAnchorW : public Wt::WAnchor {
  public:
    UserAnchorW(const std::string prefix, const User& user);
    ~UserAnchorW() = default;

  private:
    Wt::Signal<const Node&, const User&> user_clicked_;
    User user_;
    
};

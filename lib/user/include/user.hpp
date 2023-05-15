#pragma once

#include <Wt/WGlobal.h>
#include <Wt/Dbo/Types.h>

class User;
using AuthInfo = Wt::Auth::Dbo::AuthInfo<User>;

class User {
 public:
  // ...
  
  template <class Action>
  void persist(Action& a) {
    // ...
  }
};

DBO_EXTERN_TEMPLATES(User);

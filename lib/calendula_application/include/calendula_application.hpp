#pragma once

#include <Wt/WApplication.h>
#include <Wt/WGlobal.h>

#include "session.hpp"

class CalendulaApplication : public Wt::WApplication {
 public:
  CalendulaApplication(const Wt::WEnvironment& env);
 private:
  void AuthEvent();
  
  Session session_;
};

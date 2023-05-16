#pragma once

#include <Wt/WApplication.h>
#include <Wt/WGlobal.h>

#include "session.hpp"

class Application : public Wt::WApplication {
 public:
  Application(const Wt::WEnvironment& env);
 private:
  void AuthEvent();
  
  Session session_;
};

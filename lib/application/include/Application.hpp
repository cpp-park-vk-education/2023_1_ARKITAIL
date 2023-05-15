#pragma once

#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>

#include <string>
#include <unordered_map>

#include "PageWidget.hpp"
#include "Swapable.hpp"
#include "UnmetDeps.hpp"
#include "navbar_w.hpp"

class Application : public Wt::WApplication {
  public:
    Application(const Wt::WEnvironment& env);

    void route(const std::string& internalPath);

  private:
    Session session_;

    std::unordered_map<std::string, Swapable> pages_;
    Swapable cur_swap_;
    PageWidget* cur_page_;

    NavbarW* navbar_;
};

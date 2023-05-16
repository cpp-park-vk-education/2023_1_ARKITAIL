#pragma once

#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WContainerWidget.h>

#include <string>
#include <unordered_map>

#include "ConnectionsMediator.hpp"
#include "Swapable.hpp"
#include "UnmetDeps.hpp"
#include "navbar_w.hpp"
#include "Managers.hpp"

class Application : public Wt::WApplication {
  public:
    Application(const Wt::WEnvironment& env);

    void route(const std::string& internalPath);

  private:
    Session session_;

    std::unordered_map<std::string, Swapable<Wt::WContainerWidget>> pages_;
    Swapable<Wt::WContainerWidget> cur_swap_;
    Wt::WContainerWidget* cur_page_;

    NavbarW* navbar_;
};

#pragma once

#include <Wt/Dbo/Session.h>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WEnvironment.h>

#include <string>
#include <unordered_map>

#include "ConnectionsMediator.hpp"
#include "Managers.hpp"
#include "Swapable.hpp"
#include "navbar_w.hpp"

class Application : public Wt::WApplication {
  public:
    Application(const Wt::WEnvironment& env);

    void route(const std::string& internalPath);

  private:
    std::unique_ptr<Wt::Dbo::Session> session_;

    std::unordered_map<std::string, Swapable<Wt::WContainerWidget>> pages_;
    Swapable<Wt::WContainerWidget> cur_swap_;
    Wt::WContainerWidget* cur_page_;

    NavbarW* navbar_;
};

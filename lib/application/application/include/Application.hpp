#pragma once

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WEnvironment.h>

#include <Wt/WGlobal.h>
#include <string>
#include <unordered_map>

#include "ConnectionsMediator.hpp"
#include "Managers.hpp"
#include "Swapable.hpp"
#include "navbar_w.hpp"
#include "IDeferred.hpp"

class Application : public Wt::WApplication {
  public:
    explicit Application(const Wt::WEnvironment& env);

    void route(const std::string& internalPath);

  private:
    std::unique_ptr<Wt::Auth::AuthWidget> CreateAuthWiget();

    std::unordered_map<std::string, Swapable<IDeferred<Wt::WContainerWidget>>> pages_;
    Swapable<IDeferred<Wt::WContainerWidget>> cur_swap_;
    Wt::WContainerWidget* cur_page_;

    NavbarW* navbar_;
};

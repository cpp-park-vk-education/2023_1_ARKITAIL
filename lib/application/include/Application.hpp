#pragma once

#include <vector>
#include <Wt/WEnvironment.h>

#include <Wt/WApplication.h>

#include "Swapable.hpp" 
#include "UnmetDeps.hpp"

class Application : public Wt::WApplication {
public:
    Application(const Wt::WEnvironment& env);

    void route(const std::string& internalPath);
    
private:
    Session session;
    std::vector<Swapable> pages_;
    Swapable cur_page_;
    NavbarW* navbar_;

};


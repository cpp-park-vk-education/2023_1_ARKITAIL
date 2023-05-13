#pragma once

#include <string>
#include <unordered_map>
#include <Wt/WEnvironment.h>

#include <Wt/WApplication.h>

#include "PageWidget.hpp"
#include "Swapable.hpp" 
#include "UnmetDeps.hpp"

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


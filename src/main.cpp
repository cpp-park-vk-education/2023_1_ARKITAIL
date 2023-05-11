#include <iostream>

#include <Wt/WLogger.h>
#include <Wt/WApplication.h>
#include <Wt/Signals/signals.hpp>
#include <Wt/WContainerWidget.h>
#include <Wt/WEnvironment.h>
#include <Wt/WSignal.h>

#include "Application.hpp"

int main(int argc, char** argv, char** envp) {
    Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<Application>(env);
    });

    return 0;
}

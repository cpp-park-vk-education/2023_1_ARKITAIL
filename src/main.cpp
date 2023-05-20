#include <memory>

#include <Wt/WEnvironment.h>

#include "Application.hpp"

int main(int argc, char** argv) {
    Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<Application>(env);
    });

    return 0;
}

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WGlobal.h>
#include <Wt/WText.h>

#include <iostream>
#include <memory>
#include <string>

#include "calendar.hpp"

class App : public Wt::WApplication {
public:
    App(const Wt::WEnvironment& env) : 
        Wt::WApplication(env),
        c1(new CalendarRootWidget("/helo", "helo")),
        c2(new CalendarRootWidget("/bui", "bui")) {

        std::cout << "__C_o_n_n_e_c_t_i_o_n__E_s_t_a_b_l_i_s_h_e_d__" << std::endl;

        this->root()->addWidget(std::unique_ptr<CalendarRootWidget>(this->c1));
        this->c0 = this->c1;

        Wt::WApplication::instance()->internalPathChanged().connect(this, &App::route);
    }

    void route(const std::string& internalPath) {
        std::cout << "internal path changed " << internalPath << std::endl;
        auto tmp = this->root()->removeWidget(this->c0);
        this->root()->addWidget(std::move(tmp));
    }

    ~App() {
        std::cout << "__C_o_n_n_e_c_t_i_o_n__L_o_s_t__" << std::endl;
    }

private:
    CalendarRootWidget* c1;
    CalendarRootWidget* c2;

    CalendarRootWidget* c0;

};

int main(int argc, char** argv, char** envp) {
    Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<App>(env);
    });
    return 0;
}

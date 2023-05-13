#pragma once

#include <Wt/WAnchor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLink.h>
#include <string>

class PageWidget : public Wt::WContainerWidget {
public:
    PageWidget(const std::string&);

private:
    void init();

    Wt::WAnchor* anchor_;

};


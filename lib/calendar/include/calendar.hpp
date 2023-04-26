#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WLink.h>
#include <Wt/WText.h>

class CalendarRootWidget : public Wt::WContainerWidget {
public:
    CalendarRootWidget(const std::string& link, const std::string& title);
    
private:
    Wt::WAnchor* anchor; 
    Wt::WText* title;
};


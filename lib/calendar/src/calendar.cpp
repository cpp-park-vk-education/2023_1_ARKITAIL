#include <Wt/WAnchor.h>
#include <Wt/WLink.h>

#include <string>
#include <memory>

#include "calendar.hpp"

CalendarRootWidget::CalendarRootWidget(const std::string& link, const std::string& title) :
    anchor(this->addWidget(std::make_unique<Wt::WAnchor>(link, title))) {
    
    this->anchor->setLink(Wt::WLink(Wt::LinkType::InternalPath, link));
}


#include "public_calendar.hpp"

PublicCalendar::PublicCalendar() {
    addStyleClass("row");
    tree = addWidget(std::make_unique<Tree>());
    tree->addStyleClass("col-12 col-md-4 col-lg-3 mt-md-4 pt-lg-3 px-md-1");
    calendar = addWidget(std::make_unique<Calendar>());
    calendar->addStyleClass("col-12 col-md-8 col-lg-9");
}

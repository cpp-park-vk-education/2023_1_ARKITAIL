#include "public_calendar.hpp"

PublicCalendar::PublicCalendar() {
    tree = addWidget(std::make_unique<Tree>());
    calendar = addWidget(std::make_unique<Calendar>());
}

#include "OtherP.hpp"

#include "CalendarW.hpp"

OtherP::OtherP() { calendar_ = addWidget(std::make_unique<CalendarW>()); }

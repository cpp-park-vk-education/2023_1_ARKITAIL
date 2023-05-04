#include "MainP.hpp"

#include "CalendarW.hpp"

MainP::MainP() { calendar_ = addWidget(std::make_unique<CalendarW>()); }

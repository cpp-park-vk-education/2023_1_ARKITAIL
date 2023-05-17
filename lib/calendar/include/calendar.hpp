#pragma once

#include <Wt/WString.h>

#include "event.hpp"

struct Calendar {
  Wt::WString title;
  Wt::WString description;
  Wt::WString visibility;
  Wt::WString color;
  std::vector<EventSptr> events;
};

using CalendarSptr = std::shared_ptr<Calendar>;

#pragma once

#include <Wt/WString.h>

#include "event.hpp"

struct Calendar {
  Wt::WString summary;
  Wt::WString description;
  Wt::WString visibility;
  Wt::WString color;
  std::vector<std::size_t> event_ids;
};

using CalendarSptr = std::shared_ptr<Calendar>;

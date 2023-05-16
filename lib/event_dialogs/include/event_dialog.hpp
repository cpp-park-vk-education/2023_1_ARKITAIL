#pragma once

#include <memory>

#include <Wt/WObject.h>

#include "calendar.hpp"
#include "event.hpp"

class EventDialog {
 public:
   static void Show(
       Wt::WObject* parent,
       std::vector<std::shared_ptr<Calendar>> public_calendars,
       std::vector<std::shared_ptr<Calendar>> private_calendars,
       std::shared_ptr<Event> event = nullptr);
};

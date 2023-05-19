#pragma once

#include <memory>

#include <Wt/WDateTime.h>
#include <Wt/WDate.h>
#include <Wt/WString.h>

struct Event {
  Wt::WString summary;
  Wt::WString description;

  // каким-то образом событие должно
  // знать о своём календаре...
  Wt::WString calendar;

  Wt::WDateTime start;
  Wt::WDateTime end;
  bool is_all_day;

  bool is_recurrent;
  Wt::WString frequency;
  std::size_t interval;
  Wt::WDate until;
};

using EventSptr = std::shared_ptr<Event>;

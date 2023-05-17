#pragma once

#include <memory>

#include <Wt/WDateTime.h>
#include <Wt/WString.h>

struct Event {
  Wt::WString title;
  Wt::WString description;
  Wt::WString calendar;
  Wt::WString begin_date;
  Wt::WString begin_time;
  Wt::WString end_date;
  Wt::WString end_time;
  Wt::WString repeat;
  Wt::WString until;

  Wt::WDateTime start;
  Wt::WDateTime end;
};

using EventSptr = std::shared_ptr<Event>;

#pragma once

#include <Wt/WDateTime.h>
#include <Wt/WDate.h>

class Event;
using EventSptr = std::shared_ptr<Event>;

class Event {
 public:
  Event() = default;
  Event(
      int id,
      int calendar_id,
      std::string summary,
      std::string description,
      std::string location,
      Wt::WDateTime start,
      Wt::WDateTime end,
      Wt::WDateTime stamp,
      std::string frequency,
      int interval,
      Wt::WDate until);

  int id;
  int calendar_id;

  std::string summary;
  std::string description;
  std::string location;

  Wt::WDateTime start;
  Wt::WDateTime end;
  Wt::WDateTime stamp;

  std::string frequency;
  int interval;
  Wt::WDate until;
};

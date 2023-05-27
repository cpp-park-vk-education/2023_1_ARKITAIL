#pragma once

#include <Wt/WDateTime.h>
#include <Wt/WDate.h>
#include <Wt/WString.h>
#include <Wt/WColor.h>

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
      Wt::WDate until,
      Wt::WColor color = Wt::WColor(100, 100, 40));

  bool IsRecurrent() const;

  int id;
  int calendar_id;

  std::string summary;
  std::string description;
  std::string location;

  Wt::WColor color;

  Wt::WDateTime start;
  Wt::WDateTime end;
  Wt::WDateTime stamp;

  std::string frequency;
  int interval;
  Wt::WDate until;
};

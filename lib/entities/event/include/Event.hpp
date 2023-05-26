#pragma once

#include <cstddef>

#include <Wt/WDateTime.h>
#include <Wt/WDate.h>
#include <Wt/WString.h>

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
      Wt::WDateTime start,
      Wt::WDateTime end,
      bool is_recurrent = false,
      std::string frequency = std::string(),
      int interval = 0,
      Wt::WDate until = Wt::WDate());

  int id;
  int calendar_id;

  std::string summary;
  std::string description;

  Wt::WDateTime start;
  Wt::WDateTime end;

  bool is_recurrent;
  std::string frequency;
  int interval;
  Wt::WDate until;
};

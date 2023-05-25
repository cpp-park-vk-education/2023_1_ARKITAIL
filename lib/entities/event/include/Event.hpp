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
      size_t id,
      size_t calendar_id,
      std::string summary,
      std::string description,
      Wt::WDateTime start,
      Wt::WDateTime end,
      bool is_recurrent = false,
      std::string frequency = std::string(),
      size_t interval = 0,
      Wt::WDate until = Wt::WDate());

  size_t id;
  size_t calendar_id;

  std::string summary;
  std::string description;

  Wt::WDateTime start;
  Wt::WDateTime end;

  bool is_recurrent;
  std::string frequency;
  size_t interval;
  Wt::WDate until;
};

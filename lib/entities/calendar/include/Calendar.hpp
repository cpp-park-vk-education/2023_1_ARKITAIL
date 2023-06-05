#pragma once

#include <Wt/WColor.h>

#include <memory>
#include <string>
#include <vector>

class Calendar;
using CalendarSptr = std::shared_ptr<Calendar>;

enum class CalendarVisibility {
  kPublic,
  kPrivate,
};

class Calendar {
 public:
  Calendar() = default;
  Calendar(
      int id,
      int node_id,
      int owner_id,
      std::string summary,
      std::string description,
      CalendarVisibility visibility,
      Wt::WColor color);

  int id;
  int node_id;
  int owner_id;

  std::string summary;
  std::string description;
  CalendarVisibility visibility;
  Wt::WColor color;
};

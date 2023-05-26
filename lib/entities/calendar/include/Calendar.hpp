#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

class Calendar;
using CalendarSptr = std::shared_ptr<Calendar>;

class Calendar {
 public:
  Calendar() = default;
  Calendar(
      int id,
      int node_id,
      int owner_id,
      std::string summary,
      std::string description,
      std::string visibility = std::string(),
      std::string color = std::string());

  int id;
  int node_id;
  int owner_id;

  std::string summary;
  std::string description;
  std::string visibility;
  std::string color;
};

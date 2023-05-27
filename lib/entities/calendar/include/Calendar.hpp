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
  // Для сохранения работоспособности некоторых тестов
  // добавленные поля определены в конструкторе по умолчанию
  Calendar(
      size_t id,
      size_t node_id,
      size_t owner_id,
      std::string summary,
      std::string description,
      std::string visibility = std::string(),
      std::string color = "#FFDAB9");

  size_t id;
  size_t node_id;
  size_t owner_id;

  std::string summary;
  std::string description;
  std::string visibility;
  std::string color;
};

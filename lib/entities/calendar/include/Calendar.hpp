#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include <Wt/WString.h>

class Calendar;
using CalendarSptr = std::shared_ptr<Calendar>;

class Calendar {
 public:
  Calendar() = default;
  // Для сохранения работоспособности db_manages/db_mock новым
  // значениям Calendar было установлено значение "" по умолчанию
  Calendar(
      size_t id,
      size_t node_id,
      size_t owner_id,
      const Wt::WString& summary,
      const Wt::WString& description,
      const Wt::WString& visibility = "",
      const Wt::WString& color = "",
      const std::vector<size_t>& events_id = std::vector<size_t>());

  // getter'ы
  size_t id() const;
  size_t node_id() const;
  size_t owner_id() const;

  const Wt::WString& summary() const;
  const Wt::WString& description() const;
  const Wt::WString& visibility() const;
  const Wt::WString& color() const;

  const std::vector<size_t>& events_id() const;

  // setter'ы
  void set_id(size_t id);
  void set_node_id(size_t node_id);
  void set_owner_id(size_t owner_id);

  void set_summary(const Wt::WString& summary);
  void set_description(const Wt::WString& description);
  void set_visibility(const Wt::WString& visibility);
  void set_color(const Wt::WString& color);

  void set_events_id(const std::vector<size_t>& events_id);
 private:
  size_t id_;
  size_t node_id_;
  size_t owner_id_;

  Wt::WString summary_;
  Wt::WString description_;
  Wt::WString visibility_;
  Wt::WString color_;

  std::vector<size_t> events_id_;
};

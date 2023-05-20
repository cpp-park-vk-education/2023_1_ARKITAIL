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
      const Wt::WString& summary,
      const Wt::WString& description,
      const Wt::WDateTime& start,
      const Wt::WDateTime& end,
      bool is_all_day = false,
      bool is_recurrent = false,
      const Wt::WString& frequency = Wt::WString(),
      size_t interval = 0,
      const Wt::WDate& until = Wt::WDate());

  // getter'ы
  size_t id() const;
  size_t calendar_id() const;

  const Wt::WString& summary() const;
  const Wt::WString& description() const;

  const Wt::WDateTime& start() const;
  const Wt::WDateTime& end() const;
  bool is_all_day() const;

  bool is_recurrent() const;
  const Wt::WString& frequency() const;
  size_t interval() const;
  const Wt::WDate& until() const;

  // setter'ы
  void set_id(size_t id);
  void set_calendar_id(size_t calendar_id);

  void set_summary(const Wt::WString& summary);
  void set_description(const Wt::WString& description);

  void set_start(const Wt::WDateTime& start);
  void set_end(const Wt::WDateTime& end);
  void set_is_all_day(bool is_all_day);

  void set_is_reccurent(bool is_recurrent);
  void set_frequency(const Wt::WString& frequency);
  void set_interval(size_t interval);
  void set_until(const Wt::WDate& until);
 private:
  size_t id_;
  size_t calendar_id_;

  Wt::WString summary_;
  Wt::WString description_;

  Wt::WDateTime start_;
  Wt::WDateTime end_;
  bool is_all_day_;

  bool is_recurrent_;
  Wt::WString frequency_;
  size_t interval_;
  Wt::WDate until_;
};

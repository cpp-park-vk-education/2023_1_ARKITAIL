#include "Event.hpp"

Event::Event(
    size_t id,
    size_t calendar_id,
    const Wt::WString& summary,
    const Wt::WString& description,
    const Wt::WDateTime& start,
    const Wt::WDateTime& end,
    bool is_all_day,
    bool is_recurrent,
    const Wt::WString& frequency,
    size_t interval,
    const Wt::WDate& until)
  : id_(id),
    calendar_id_(calendar_id),
    summary_(summary),
    description_(description),
    start_(start),
    end_(end),
    is_all_day_(is_all_day),
    is_recurrent_(is_recurrent),
    frequency_(frequency),
    interval_(interval),
    until_(until) {
}

// getter'ы

size_t Event::id() const {
  return id_;
}

size_t Event::calendar_id() const {
  return calendar_id_;
}

const Wt::WString& Event::summary() const {
  return summary_;
}

const Wt::WString& Event::description() const {
  return description_;
}

const Wt::WDateTime& Event::start() const {
  return start_;
}

const Wt::WDateTime& Event::end() const {
  return end_;
}

bool Event::is_all_day() const {
  return is_all_day_;
}

bool Event::is_recurrent() const {
  return is_recurrent_;
}

const Wt::WString& Event::frequency() const {
  return frequency_;
}

size_t Event::interval() const {
  return interval_;
}

const Wt::WDate& Event::until() const {
  return until_;
}

// setter'ы

void Event::set_id(size_t id) {
  id_ = id;
}

void Event::set_calendar_id(size_t calendar_id) {
  calendar_id_ = calendar_id;
}

void Event::set_summary(const Wt::WString& summary) {
  summary_ = summary;
}

void Event::set_description(const Wt::WString& description) {
  description_ = description;
}

void Event::set_start(const Wt::WDateTime& start) {
  start_ = start;
}

void Event::set_end(const Wt::WDateTime& end) {
  end_ = end;
}

void Event::set_is_all_day(bool is_all_day) {
  is_all_day_ = is_all_day;
}

void Event::set_is_reccurent(bool is_recurrent) {
  is_recurrent_ = is_recurrent;
}

void Event::set_frequency(const Wt::WString& frequency) {
  frequency_ = frequency;
}

void Event::set_interval(size_t interval) {
  interval_ = interval;
}

void Event::set_until(const Wt::WDate& until) {
  until_ = until;
}

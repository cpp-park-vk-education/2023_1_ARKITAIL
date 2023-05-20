#include "Calendar.hpp"

#include <cstddef>
#include <vector>

#include <Wt/WString.h>

Calendar::Calendar(
    size_t id,
    size_t node_id,
    size_t owner_id,
    const Wt::WString& summary,
    const Wt::WString& description,
    const Wt::WString& visibility,
    const Wt::WString& color,
    const std::vector<size_t>& events_id) 
  : id_(id),
    node_id_(node_id),
    owner_id_(owner_id),
    summary_(summary),
    description_(description),
    visibility_(visibility),
    color_(color),
    events_id_(events_id) {
}

// getter'ы

size_t Calendar::id() const {
  return id_;
}

size_t Calendar::node_id() const {
  return node_id_;
}

size_t Calendar::owner_id() const {
  return owner_id_;
}

const Wt::WString& Calendar::summary() const {
  return summary_;
}

const Wt::WString& Calendar::description() const {
  return description_;
}

const Wt::WString& Calendar::visibility() const {
  return visibility_;
}

const Wt::WString& Calendar::color() const {
  return color_;
}

const std::vector<size_t>& Calendar::events_id() const {
  return events_id_;
}

// setter'ы

void Calendar::set_id(size_t id) {
  id_ = id;
}

void Calendar::set_node_id(size_t node_id) {
  node_id_ = node_id;
}

void Calendar::set_owner_id(size_t owner_id) {
  owner_id_ = owner_id;
}

void Calendar::set_summary(const Wt::WString& summary) {
  summary_ =summary;
}

void Calendar::set_description(const Wt::WString& description) {
  description_ = description;
}

void Calendar::set_visibility(const Wt::WString& visibility) {
  visibility_ = visibility;
}

void Calendar::set_color(const Wt::WString& color) {
  color_ = color;
}

void Calendar::set_events_id(const std::vector<size_t>& events_id) {
  events_id_ = events_id;
}

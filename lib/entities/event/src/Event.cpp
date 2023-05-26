#include "Event.hpp"
#include <string>

Event::Event(
    int id,
    int calendar_id,
    std::string summary,
    std::string description,
    Wt::WDateTime start,
    Wt::WDateTime end,
    bool is_recurrent,
    std::string frequency,
    int interval,
    Wt::WDate until)
  : id(id),
    calendar_id(calendar_id),
    summary(std::move(summary)),
    description(std::move(description)),
    start(std::move(start)),
    end(std::move(end)),
    is_recurrent(is_recurrent),
    frequency(std::move(frequency)),
    interval(interval),
    until(std::move(until)) {
}

#include "Event.hpp"

#include <Wt/WColor.h>
#include <string>

Event::Event(
    int id,
    int calendar_id,
    std::string summary,
    std::string description,
    std::string location,
    Wt::WDateTime start,
    Wt::WDateTime end,
    Wt::WDateTime stamp,
    std::string frequency,
    int interval,
    Wt::WDate until,
    Wt::WColor color)
  : id(id),
    calendar_id(calendar_id),
    summary(std::move(summary)),
    description(std::move(description)),
    location(std::move(location)),
    start(std::move(start)),
    end(std::move(end)),
    stamp(std::move(stamp)),
    frequency(std::move(frequency)),
    interval(interval),
    until(std::move(until)),
    color(std::move(color)) {
}

// если событие не повторяется, то frequency == "",
// interval == 0 и until == Wt::WDate()
bool Event::IsRecurrent() const {
  return frequency == "";
}

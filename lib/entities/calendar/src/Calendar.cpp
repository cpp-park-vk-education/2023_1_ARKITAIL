#include "Calendar.hpp"

Calendar::Calendar(
    int id,
    int node_id,
    int owner_id,
    std::string summary,
    std::string description,
    CalendarVisibility visibility,
    Wt::WColor color)
  : id(id),
    node_id(node_id),
    owner_id(owner_id),
    summary(std::move(summary)),
    description(std::move(description)),
    visibility(visibility),
    color(std::move(color)) {
}

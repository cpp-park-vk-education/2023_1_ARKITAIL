#include "Calendar.hpp"

#include <cstddef>
#include <vector>
#include <string>

Calendar::Calendar(
    size_t id,
    size_t node_id,
    size_t owner_id,
    std::string summary,
    std::string description,
    std::string visibility,
    std::string color)
  : id(id),
    node_id(node_id),
    owner_id(owner_id),
    summary(summary),
    description(description),
    visibility(visibility),
    color(color) {
}

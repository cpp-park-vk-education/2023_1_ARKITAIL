#include "Calendar.hpp"

#include <cstddef>
#include <vector>
#include <string>

Calendar::Calendar(
    int id,
    int node_id,
    int owner_id,
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

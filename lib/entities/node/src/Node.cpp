#include "Node.hpp"

#include <cstddef>

Node::Node(int id, int parent_id, int resource_id, NodeType type) :
    id(id),
    parent_id(parent_id),
    resource_id(resource_id),
    type(type) {}

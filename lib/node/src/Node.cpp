#include <cstddef>

#include "Node.hpp"

Node::Node(size_t id, size_t parent_id, size_t resource_id, NodeType type) : 
    id(id),
    parent_id(parent_id),
    resource_id(resource_id),
    type(type) {}

Node::Node(const Node& node) :
    Node(node.id, node.parent_id, node.resource_id, node.type) {}


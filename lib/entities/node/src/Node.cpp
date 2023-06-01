#include "Node.hpp"

Node::Node(int id, int parent_id, int resource_id, int owner_id, NodeType type)
    : id(id),
      parent_id(parent_id),
      resource_id(resource_id),
      owner_id(owner_id),
      type(type) {
}

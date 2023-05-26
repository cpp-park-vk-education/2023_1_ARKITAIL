#pragma once

#include <vector>

#include "Node.hpp"
#include "Tag.hpp"

class INodeDbManager {
public:
  virtual const Node &get(int node_id) = 0;
  virtual int add(const Node &) = 0;
  virtual void update(const Node &) = 0;
  virtual void remove(int node_id) = 0;

  virtual std::vector<Node> getChildren(int node_id) = 0;
  // virtual void tag(int node_id, const Tag &);
  // virtual void move(int node_id, int destination_id);
};

#pragma once

#include <vector>

#include "Node.hpp"
#include "Tag.hpp"

class INodeDbManager {
public:
  virtual NodeSptr get(int node_id) = 0;
  virtual int add(NodeSptr node) = 0;
  virtual void update(NodeSptr node) = 0;
  virtual void remove(int node_id) = 0;

  virtual std::vector<Node> getChildren(int node_id) = 0;
  virtual void tag(int node_id, int tag_id) = 0;
  virtual std::vector<TagSptr> tagByNode(int node_id) = 0;

};


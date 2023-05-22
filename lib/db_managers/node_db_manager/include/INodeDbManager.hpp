#pragma once

#include <vector>

#include "Node.hpp"

class INodeDbManager {
  public:
    virtual const Node& get(int) = 0;
    virtual int add(const Node&) = 0;
    virtual void update(const Node&) = 0;
    virtual void remove(int) = 0;

    virtual std::vector<Node> getChildren(int) = 0;
};


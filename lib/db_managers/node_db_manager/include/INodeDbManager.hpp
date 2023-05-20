#pragma once

#include <vector>

#include "Node.hpp"

class INodeDbManager {
  public:
    virtual const Node& get(size_t) = 0;
    virtual size_t add(const Node&) = 0;
    virtual void update(const Node&) = 0;
    virtual void remove(size_t) = 0;

    virtual std::vector<Node> getChildren(size_t) = 0;
};


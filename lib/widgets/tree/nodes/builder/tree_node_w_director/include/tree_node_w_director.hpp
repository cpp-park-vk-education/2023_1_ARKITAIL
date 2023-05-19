#pragma once

#include <memory>

#include "ITreeNode.hpp"
#include "Node.hpp"

class TreeNodeW;

struct {
    /* data */
};

class TreeNodeWDirector {
  public:
    TreeNodeWDirector();

    std::unique_ptr<TreeNodeW> createNode(TreeNodeWType type, ITreeNode* this_node,
                                          TreeNodeW* parent_node);
};

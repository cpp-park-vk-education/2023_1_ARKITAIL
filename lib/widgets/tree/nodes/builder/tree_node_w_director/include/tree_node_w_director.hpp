#pragma once

#include <memory>

#include "ITreeNode.hpp"
#include "Node.hpp"
#include "tree_node_w_analyst.hpp"

class TreeNodeW;

class TreeNodeWDirector {
  public:
    TreeNodeWDirector();

    std::unique_ptr<TreeNodeW> createNode(TreeNodeWConvertedData data, TreeNodeW* parent_node);
};

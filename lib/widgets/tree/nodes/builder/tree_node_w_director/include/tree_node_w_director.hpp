#pragma once

#include <memory>

#include "ITreeNode.hpp"
#include "Node.hpp"
#include "tree_node_w_analyst.hpp"
#include "tree_node_w_builder.hpp"

class TreeNodeW;

class TreeNodeWDirector {
  public:
    TreeNodeWDirector();

    std::unique_ptr<TreeNodeW> fillNode(TreeNodeWConvertedData data, TreeNodeWBuilder& builder);
};

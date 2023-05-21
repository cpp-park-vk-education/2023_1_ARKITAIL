#pragma once

#include <memory>

#include "ITreeNode.hpp"
#include "tree_node_w_builder_base.hpp"

class TreeNodeW;

class TreeNodeLeafWBuilder : public TreeNodeWBuilderBase {
  public:
    TreeNodeLeafWBuilder();
    TreeNodeLeafWBuilder* createTreeNodeW(ITreeNode* node);

    std::unique_ptr<TreeNodeW> getTreeNodeW();
};

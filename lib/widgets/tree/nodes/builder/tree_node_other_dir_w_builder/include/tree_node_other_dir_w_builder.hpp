#pragma once

#include <memory>

#include "ITreeNode.hpp"
#include "tree_node_w_builder_base.hpp"

class TreeNodeOtherDirWBuilder : public TreeNodeWBuilderBase {
  public:
    TreeNodeOtherDirWBuilder();
    TreeNodeOtherDirWBuilder* createTreeNodeW(ITreeNode* node);

    std::unique_ptr<TreeNodeW> getTreeNodeW();
};

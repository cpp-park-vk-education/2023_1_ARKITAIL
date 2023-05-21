#pragma once

#include <memory>

#include "ITreeNode.hpp"
#include "tree_node_w_builder_base.hpp"

class TreeNodeSubDirWBuilder : public TreeNodeWBuilderBase {
  public:
    TreeNodeSubDirWBuilder();
    TreeNodeSubDirWBuilder* createTreeNodeW(ITreeNode* node);

    std::unique_ptr<TreeNodeW> getTreeNodeW();
};

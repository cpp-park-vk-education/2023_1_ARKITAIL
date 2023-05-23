#pragma once

#include <memory>

#include "ITreeNode.hpp"
#include "tree_node_w_builder_base.hpp"

class TreeNodeW;

class TreeNodeDirWBuilder : public TreeNodeWBuilderBase {
  public:
    TreeNodeDirWBuilder();
    ~TreeNodeDirWBuilder() = default;
    TreeNodeDirWBuilder* createTreeNodeW(ITreeNode* node);

    std::unique_ptr<TreeNodeW> getTreeNodeW();
};

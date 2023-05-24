#pragma once

#include <memory>

#include "ITreeNode.hpp"
#include "TreeNodeWBuilderBase.hpp"

class TreeNodeW;

class TreeNodeLeafWBuilder : public TreeNodeWBuilderBase {
  public:
    TreeNodeLeafWBuilder();
    ~TreeNodeLeafWBuilder() = default;
    TreeNodeLeafWBuilder* createTreeNodeW(ITreeNode* node);

    std::unique_ptr<TreeNodeW> getTreeNodeW();
};

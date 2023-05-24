#pragma once

#include <memory>

#include "ITreeNode.hpp"
#include "TreeNodeWBuilderBase.hpp"

class TreeNodeW;

class TreeNodeDirWBuilder : public TreeNodeWBuilderBase {
  public:
    TreeNodeDirWBuilder();
    ~TreeNodeDirWBuilder() = default;
    TreeNodeDirWBuilder* createTreeNodeW(ITreeNode* node) override;

    std::unique_ptr<TreeNodeW> getTreeNodeW() override;
};

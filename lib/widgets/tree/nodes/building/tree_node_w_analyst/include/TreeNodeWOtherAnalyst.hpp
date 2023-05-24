#pragma once

#include "ITreeNode.hpp"
#include "ITreeNodeWAnalyst.hpp"

class TreeNodeWOtherAnalyst : public ITreeNodeWAnalyst {
  public:
    TreeNodeWOtherAnalyst();
    ~TreeNodeWOtherAnalyst() = default;

    TreeNodeWConvertedData analyseTreeNodeWChild(ITreeNode* tree_node) override;
};

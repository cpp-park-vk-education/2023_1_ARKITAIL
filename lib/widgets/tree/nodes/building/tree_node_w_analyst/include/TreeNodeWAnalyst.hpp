#pragma once

#include "ITreeNode.hpp"
#include "ITreeNodeWAnalyst.hpp"

class TreeNodeWAnalyst : public ITreeNodeWAnalyst {
  public:
    TreeNodeWAnalyst();
    ~TreeNodeWAnalyst() = default;

    TreeNodeWConvertedData analyseTreeNodeWChild(ITreeNode* tree_node) override;
};

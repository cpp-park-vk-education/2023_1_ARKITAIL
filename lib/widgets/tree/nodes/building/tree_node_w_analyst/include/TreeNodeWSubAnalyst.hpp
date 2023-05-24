#pragma once

#include "ITreeNode.hpp"
#include "ITreeNodeWAnalyst.hpp"

class TreeNodeWSubAnalyst : public ITreeNodeWAnalyst {
  public:
    TreeNodeWSubAnalyst();
    ~TreeNodeWSubAnalyst() = default;

    TreeNodeWConvertedData analyseTreeNodeWChild(ITreeNode* tree_node) override;
};

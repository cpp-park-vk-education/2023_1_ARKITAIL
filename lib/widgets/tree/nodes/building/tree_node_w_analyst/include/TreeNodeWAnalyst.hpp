#pragma once

#include "ITreeNode.hpp"
#include "TreeNodeWAnalystBase.hpp"

class TreeNodeWAnalyst : public TreeNodeWAnalystBase {
  public:
    TreeNodeWAnalyst();
    TreeNodeWAnalyst(IManagers* managers);
    ~TreeNodeWAnalyst() = default;

    TreeNodeWConvertedData analyseTreeNodeWChild(ITreeNode* tree_node) override;
};

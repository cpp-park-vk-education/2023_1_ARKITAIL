#pragma once

#include "ITreeNode.hpp"
#include "TreeNodeWAnalystBase.hpp"

class TreeNodeWOtherAnalyst : public TreeNodeWAnalystBase {
  public:
    TreeNodeWOtherAnalyst();
    TreeNodeWOtherAnalyst(IManagers* managers);
    ~TreeNodeWOtherAnalyst() = default;

    TreeNodeWConvertedData analyseTreeNodeWChild(ITreeNode* tree_node) override;
};

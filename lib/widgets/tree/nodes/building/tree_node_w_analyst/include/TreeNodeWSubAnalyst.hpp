#pragma once

#include "ITreeNode.hpp"
#include "TreeNodeWAnalystBase.hpp"

class TreeNodeWSubAnalyst : public TreeNodeWAnalystBase {
  public:
    TreeNodeWSubAnalyst() {}
    TreeNodeWSubAnalyst(IManagers* managers);
    ~TreeNodeWSubAnalyst() = default;

    TreeNodeWConvertedData analyseTreeNodeWChild(ITreeNode* tree_node) override;
};

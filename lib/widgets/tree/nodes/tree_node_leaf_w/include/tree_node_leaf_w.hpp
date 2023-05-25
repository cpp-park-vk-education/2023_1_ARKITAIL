#pragma once

#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>

#include <memory>

#include "ITreeNode.hpp"
#include "tree_node_w.hpp"

class TreeNodeLeafW : public TreeNodeW {
  public:
    TreeNodeLeafW();
    TreeNodeLeafW(ITreeNode* node);
    ~TreeNodeLeafW() = default;

    void checkNode() override;
    void uncheckNode() override;
    void performAction(Action action) override;
};

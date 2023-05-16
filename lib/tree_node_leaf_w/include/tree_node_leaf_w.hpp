#pragma once

#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>

#include <memory>

#include "tree_node_w.hpp"

class TreeNodeLeafW : public TreeNodeW {
  public:
    TreeNodeLeafW(ITreeNode* node);
    ~TreeNodeLeafW() = default;

    void showNode() override;
    void closeNode() override;
    void checkNode() override;
    void uncheckNode() override;

    void performAction(Action action) override;
};

#pragma once

#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>

#include <memory>

#include "tree_node_w.hpp"

class TreeNodeLeaveW : public TreeNodeW {
  public:
    TreeNodeLeaveW();
    ~TreeNodeLeaveW() = default;

    void showNode() override;
    void closeNode() override;
    void checkNode() override;
    void uncheckNode() override;
};

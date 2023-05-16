#pragma once

#include <Wt/WText.h>

#include "tree_node_leaf_w.hpp"

class TreeNodeCalendarW : public TreeNodeLeafW {
  public:
    TreeNodeCalendarW(std::string label, ITreeNode* node);
    ~TreeNodeCalendarW() = default;
    Wt::WInteractWidget* getTitle() override;
    void performAction(Action action) override;

  private:
    Wt::WText* label_;
};

#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WIconPair.h>
#include <Wt/WText.h>

#include <memory>
#include <string>
#include <vector>

#include "tree_node_dir_w.hpp"

class TreeNodeSubscriptionsGroupW : public TreeNodeDirW {
  public:
    TreeNodeSubscriptionsGroupW(std::string label, ITreeNode* node);
    ~TreeNodeSubscriptionsGroupW() = default;

    std::unique_ptr<TreeNodeW> makeTreeNodeWidget(ITreeNode* node) override;
};

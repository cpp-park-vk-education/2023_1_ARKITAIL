#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WIconPair.h>
#include <Wt/WText.h>

#include <memory>
#include <string>
#include <vector>

#include "tree_node_dir_w.hpp"

class TreeNodeSubscriptionsDirW : public TreeNodeDirW {
  public:
    TreeNodeSubscriptionsDirW(ITreeNode* node);
    ~TreeNodeSubscriptionsDirW() = default;

    std::unique_ptr<TreeNodeW> makeTreeNodeWidget(ITreeNode* node) override;
};

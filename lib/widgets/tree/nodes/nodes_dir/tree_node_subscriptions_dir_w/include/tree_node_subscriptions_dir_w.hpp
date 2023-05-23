#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WIconPair.h>
#include <Wt/WText.h>

#include <memory>
#include <string>
#include <vector>

#include "ITreeNode.hpp"
#include "tree_node_dir_w.hpp"
#include "tree_node_w.hpp"

class TreeNodeSubscriptionsDirW : public TreeNodeDirW {
  public:
    TreeNodeSubscriptionsDirW();
    TreeNodeSubscriptionsDirW(ITreeNode* node);
    ~TreeNodeSubscriptionsDirW() = default;

    std::unique_ptr<TreeNodeW> makeTreeNodeWidget(ITreeNode* node) override;
};

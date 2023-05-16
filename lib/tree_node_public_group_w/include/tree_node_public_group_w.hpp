#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WIconPair.h>
#include <Wt/WText.h>

#include <memory>
#include <string>
#include <vector>

#include "tree_node_dir_w.hpp"

class TreeNodePublicGroupW : public TreeNodeDirW {
  public:
    TreeNodePublicGroupW(std::string label, TreeNode* node);
    ~TreeNodePublicGroupW() = default;

    std::unique_ptr<TreeNodeW> makeTreeNodeWidget(TreeNode* node) override;
};

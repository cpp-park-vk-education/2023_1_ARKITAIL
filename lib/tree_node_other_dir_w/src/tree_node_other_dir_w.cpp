#include "tree_node_other_dir_w.hpp"

#include <memory>

#include "Wt/WContainerWidget.h"
#include "Wt/WIconPair.h"
#include "Wt/WText.h"
#include "tree_node_dir_w.hpp"

TreeNodeOtherDirW::TreeNodeOtherDirW(std::string label, TreeNode* node) : TreeNodeDirW(label, node) {}

std::unique_ptr<TreeNodeW> TreeNodeOtherDirW::makeTreeNodeWidget(TreeNode* node) {}

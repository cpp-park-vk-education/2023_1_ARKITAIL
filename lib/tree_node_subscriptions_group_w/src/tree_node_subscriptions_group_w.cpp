#include "tree_node_subscriptions_group_w.hpp"

#include <memory>

#include "Node.hpp"
#include "Wt/WContainerWidget.h"
#include "Wt/WIconPair.h"
#include "Wt/WText.h"
#include "tree_node_dir_w.hpp"
#include "tree_node_w.hpp"

TreeNodeSubscriptionsGroupW::TreeNodeSubscriptionsGroupW(std::string label, TreeNode* node)
    : TreeNodeDirW(label, node) {}

std::unique_ptr<TreeNodeW> TreeNodeSubscriptionsGroupW::makeTreeNodeWidget(TreeNode* node) {}

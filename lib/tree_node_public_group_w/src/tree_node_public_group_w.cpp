#include "tree_node_public_group_w.hpp"

#include <memory>

#include "Wt/WContainerWidget.h"
#include "Wt/WIconPair.h"
#include "Wt/WText.h"
#include "tree_node_dir_w.hpp"

TreeNodePublicGroupW::TreeNodePublicGroupW(std::string label, ITreeNode* node) : TreeNodeDirW(label, node) {}

std::unique_ptr<TreeNodeW> TreeNodePublicGroupW::makeTreeNodeWidget(ITreeNode* node) {}

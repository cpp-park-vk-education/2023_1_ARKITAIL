#include "tree_node_leaf_w.hpp"

#include <memory>

#include "options_w_builder.hpp"
#include "options_w_director.hpp"
#include "tree_node_w.hpp"

TreeNodeLeafW::TreeNodeLeafW() {}

TreeNodeLeafW::TreeNodeLeafW(ITreeNode* node) :
    TreeNodeW(node) {}

void TreeNodeLeafW::checkNode() {
    check_box_->setChecked(true);
}

void TreeNodeLeafW::uncheckNode() {
    uncheckParentNodes();
}

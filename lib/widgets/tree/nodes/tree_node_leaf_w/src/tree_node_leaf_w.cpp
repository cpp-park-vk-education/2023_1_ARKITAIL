#include "tree_node_leaf_w.hpp"

#include <memory>

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

void TreeNodeLeafW::showNode() {}

void TreeNodeLeafW::closeNode() {}

void TreeNodeLeafW::performAction(Action action) {}

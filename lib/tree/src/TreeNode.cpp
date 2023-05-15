#include <vector>

#include "TreeNode.hpp"

TreeNode::TreeNode(const Node& node) :
    node_(node),
    children_(),
    checked_(false) {

}

const Node& TreeNode::getNode() {
    return node_;
}

std::vector<TreeNode*> TreeNode::getChildren() const {
    return children_;
}

void TreeNode::check() {
    checked_ = !checked_;
}

bool TreeNode::isChecked() {
    return checked_;
}


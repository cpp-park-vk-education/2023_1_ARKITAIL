#include <vector>

#include "TreeNode.hpp"

TreeNode::TreeNode(const Node& node) :
    node(node),
    childs(),
    checked(false) {}

const Node& TreeNode::getNode() {
    return this->node;
}

std::vector<TreeNode*> TreeNode::getChilds() const {
    return std::vector<TreeNode*>();
}

void TreeNode::check() {}

bool TreeNode::isChecked() {
    return false;
}


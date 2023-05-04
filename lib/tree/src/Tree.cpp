#include <vector>

#include "Tree.hpp"
#include "Node.hpp"
#include "TreeNode.hpp"

Tree::Tree(const Node& node) :
    root(TreeNode(node)),
    checked_count(0) {}

TreeNode* Tree::insertNode(const TreeNode& node, TreeNode* parent) {
    return nullptr;
}

void Tree::removeNode(TreeNode* node) {}

TreeNode* Tree::getRoot() {
    return &this->root;
}

std::vector<TreeNode*> Tree::getChilds(TreeNode* node) {
    return std::vector<TreeNode*>();
}

std::vector<Event> Tree::getCheckedEvents() {
    return std::vector<Event>();
}

std::vector<Event> Tree::checkNode() {
    return std::vector<Event>();
}

size_t Tree::checked() {
    return this->checked_count;
}

bool Tree::someChecked() {
    return false;
}


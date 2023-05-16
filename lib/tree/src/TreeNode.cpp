#include <memory>
#include <vector>

#include "Managers.hpp"
#include "TreeNode.hpp"

TreeNode::TreeNode(const Node& node, TreeNode* parent) :
    node_(node),
    children_(),
    checked_(false),
    parent_(parent) {
    
    for (auto c : Managers::instance().node_manager->getChildren(node.id))
        children_.emplace_back(std::make_unique<TreeNode>(c, this));
}

const Node& TreeNode::getNode() {
    return node_;
}

TreeNode* TreeNode::getParent() {
    return parent_;
}

std::vector<TreeNode*> TreeNode::getChildren() {
    std::vector<TreeNode*> children;

    for (size_t i = 0; i < children_.size(); i++)
        children.push_back(children_[i].get());

    return children;
}

TreeNode* TreeNode::addChild(std::unique_ptr<TreeNode> tree_node) {
    children_.emplace_back(std::move(tree_node));
    return children_.back().get();
}

std::unique_ptr<TreeNode> TreeNode::remove() {
    return parent_->removeChild(this);
}

void TreeNode::check() {
    checked_ = true;
}

void TreeNode::uncheck() {
    checked_ = false;
}

bool TreeNode::isChecked() {
    return checked_;
}

std::unique_ptr<TreeNode> TreeNode::removeChild(TreeNode* child) {
    std::unique_ptr<TreeNode> rmd_child;

    for (auto b = children_.begin(); b != children_.end(); b++) {
        if (b->get() == child) {
            rmd_child.swap(*b);
            children_.erase(b);
        }
    }

    return rmd_child;
}


#include "TreeNodeMock.hpp"

TreeNodeMock::TreeNodeMock(const Node& node) :
    TreeNodeMock(node, nullptr) {}

TreeNodeMock::TreeNodeMock(const Node& node, ITreeNode* parent) :
    node_(node),
    children_(),
    checked_(false),
    parent_(parent) {}

const Node& TreeNodeMock::getNode() {
    return node_;
}

ITreeNode* TreeNodeMock::getParent() {
    return parent_;
}

std::vector<ITreeNode*> TreeNodeMock::getChildren() {
    std::vector<ITreeNode*> children;

    for (int i = 0; i < children_.size(); i++)
        children.push_back(children_[i].get());

    return children;
}

ITreeNode* TreeNodeMock::addChild(const Node& node) {
    std::unique_ptr<ITreeNode> tree_node = std::make_unique<TreeNodeMock>(node, this);
    children_.emplace_back(std::move(tree_node));
    return children_.back().get();
}

std::unique_ptr<ITreeNode> TreeNodeMock::remove() {
    return parent_->removeChild(this);
}

void TreeNodeMock::check() {
    checked_ = true;
}

void TreeNodeMock::uncheck() {
    checked_ = false;
}

bool TreeNodeMock::isChecked() {
    return checked_;
}

std::unique_ptr<ITreeNode> TreeNodeMock::removeChild(ITreeNode* child) {
    std::unique_ptr<ITreeNode> rmd_child;

    for (auto b = children_.begin(); b != children_.end(); b++) {
        if (b->get() == child) {
            rmd_child.swap(*b);
            children_.erase(b);
        }
    }

    return rmd_child;
}



#include "TreeNode.hpp"

#include <iostream>
#include <memory>
#include <vector>

#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "ITreeNode.hpp"
#include "Managers.hpp"

TreeNode::TreeNode(Node node, ITreeNode* parent) : node_(node), parent_(parent), children_(), checked_(false) {
    auto mgr = SessionScopeMap::instance().get()->managers();

    for (auto c : mgr->node_manager()->getChildren(node.id)) {
        if (c.type & NodeType::MOUNT)
            children_.emplace_back(std::make_unique<TreeNode>(mgr->node_manager()->get(c.resource_id), this));
        else 
            children_.emplace_back(std::make_unique<TreeNode>(c, this));
    }
}

Node TreeNode::getNode() { return node_; }

ITreeNode* TreeNode::getParent() { return parent_; }

std::vector<ITreeNode*> TreeNode::getChildren() {
    std::vector<ITreeNode*> children;

    for (size_t i = 0; i < children_.size(); i++)
        children.push_back(children_[i].get());

    return children;
}

ITreeNode* TreeNode::addChild(Node node) {
    std::unique_ptr<ITreeNode> tree_node = std::make_unique<TreeNode>(node, this);
    children_.emplace_back(std::move(tree_node));
    return children_.back().get();
}

std::unique_ptr<ITreeNode> TreeNode::remove() { return parent_->removeChild(this); }

void TreeNode::check() { checked_ = true; }

void TreeNode::uncheck() { checked_ = false; }

bool TreeNode::isChecked() { return checked_; }

std::unique_ptr<ITreeNode> TreeNode::removeChild(ITreeNode* child) {
    std::unique_ptr<ITreeNode> rmd_child;

    for (auto b = children_.begin(); b != children_.end(); b++) {
        if (b->get() == child) {
            rmd_child.swap(*b);
            children_.erase(b);
        }
    }

    return rmd_child;
}

#include "TreeNode.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "ITreeNode.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"

TreeNode::TreeNode(NodeSptr node) :
    TreeNode(node, nullptr) {}

TreeNode::TreeNode(NodeSptr node, ITreeNode* parent) :
    node_(node),
    parent_(parent),
    children_(),
    checked_(false) {
    Wt::log("TreeNode::TreeNode: started to handle node with id " + std::to_string(node->id));
    auto mgr = SessionScopeMap::instance().get()->managers();
    for (auto child : mgr->node_manager()->getChildren(node->id)) {
        if (child.type & MOUNT) {
          Wt::log("TreeNode::TreeNode: requesting mount_node with id " + std::to_string(child.resource_id));
          auto mount_node = mgr->node_manager()->get(child.resource_id);
          Wt::log("TreeNode::TreeNode: mount_node with id " + std::to_string(child.resource_id) + " is nullptr: " + std::to_string(mount_node == nullptr));
          children_.emplace_back(std::make_unique<TreeNode>(mount_node, this));
        } else {
          Wt::log("TreeNode::TreeNode: emplacing child with id " + std::to_string(child.id));
          children_.emplace_back(std::make_unique<TreeNode>(std::make_shared<Node>(std::move(child)), this));
        }
    }
    Wt::log("TreeNode::TreeNode: handled node with id " + std::to_string(node->id));
}

const Node& TreeNode::getNode() {
    return *node_;
}

ITreeNode* TreeNode::getParent() {
    return parent_;
}

std::vector<ITreeNode*> TreeNode::getChildren() {
    std::vector<ITreeNode*> children;

    for (size_t i = 0; i < children_.size(); i++)
        children.push_back(children_[i].get());

    return children;
}

ITreeNode* TreeNode::addChild(NodeSptr node) {
    std::unique_ptr<ITreeNode> tree_node = std::make_unique<TreeNode>(node, this);
    children_.emplace_back(std::move(tree_node));
    return children_.back().get();
}

std::unique_ptr<ITreeNode> TreeNode::remove() {
    return parent_->removeChild(this);
}

void TreeNode::check() {
    checked_ = true;
}

void TreeNode::uncheck() {
    std::cout << "Unchecked" << std::endl;
    checked_ = false;
}

bool TreeNode::isChecked() {
    return checked_;
}

std::unique_ptr<ITreeNode> TreeNode::removeChild(ITreeNode* child) {
    std::unique_ptr<ITreeNode> rmd_child;

    for (auto b = children_.begin(); b != children_.end(); b++) {
        if (b->get() == child) {
            rmd_child.swap(*b);
            children_.erase(b);
            break;
        }
    }

    return rmd_child;
}

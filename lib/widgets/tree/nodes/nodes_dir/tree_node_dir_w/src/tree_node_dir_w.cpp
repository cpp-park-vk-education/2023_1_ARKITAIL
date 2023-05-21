#include "tree_node_dir_w.hpp"

#include <memory>

#include "Wt/WContainerWidget.h"
#include "Wt/WIconPair.h"
#include "Wt/WText.h"
#include "options_w_builder.hpp"
#include "options_w_director.hpp"
#include "tree_node_w.hpp"

TreeNodeDirW::TreeNodeDirW() {}

TreeNodeDirW::TreeNodeDirW(ITreeNode* node) :
    TreeNodeW(node) {
    icon_ =
        node_block_->insertWidget(0,
                                  std::make_unique<Wt::WIconPair>("/static/icons/nav-plus.svg",
                                                                  "/static/icons/nav-minus.svg"),
                                  0);
    icon_->addStyleClass("me-1");
    icon_->icon1Clicked().connect(this, &TreeNodeDirW::showNode);
    icon_->icon2Clicked().connect(this, &TreeNodeDirW::closeNode);
    children_container_ = addWidget(std::make_unique<Wt::WContainerWidget>());
    children_container_->addStyleClass("ps-4");
}

TreeNodeW* TreeNodeDirW::addChildNode(std::unique_ptr<TreeNodeW> child) {
    TreeNodeW* child_node = children_container_->addWidget(std::move(child));
    child_node->addParent(this);
    children_.push_back(child_node);
    return child_node;
}

std::vector<TreeNodeW*> TreeNodeDirW::childrenNodes() {
    return children_;
}

void TreeNodeDirW::showNode() {
    if (childrenNodes().empty()) {
        for (auto&& node_child : node_->getChildren()) {
            auto child_block = addChildNode(this->makeTreeNodeWidget(node_child));
            if (isCanCheck() && check_box_->isChecked()) {
                child_block->checkNode();
            }
        }

    } else {
        for (auto&& child : childrenNodes()) {
            std::cout << "t\n";
            child->setHidden(false);
        }
    }
}

void TreeNodeDirW::closeNode() {
    for (auto&& child : childrenNodes()) {
        child->setHidden(true);
    }
}

void TreeNodeDirW::checkNode() {
    check_box_->setChecked(true);
    for (auto&& child : childrenNodes()) {
        child->checkNode();
    }
}

void TreeNodeDirW::uncheckNode() {
    uncheckParentNodes();
    for (auto&& child : childrenNodes()) {
        child->uncheckNode();
    }
}

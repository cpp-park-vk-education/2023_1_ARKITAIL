#include "TreeNodeDirW.hpp"

#include <memory>

#include <Wt/WContainerWidget.h>
#include <Wt/WIconPair.h>
#include <Wt/WText.h>

#include "Directory.hpp"
#include "EditDirectoryDialog.hpp"
#include "SessionScopeMap.hpp"
#include "TreeNodeW.hpp"

TreeNodeDirW::TreeNodeDirW() :
    TreeNodeW() {}

TreeNodeDirW::TreeNodeDirW(ITreeNode* node) :
    TreeNodeW(node),
    children_(),
    icon_(node_block_->insertWidget(0,
                                    std::make_unique<Wt::WIconPair>("/static/icons/nav-plus.svg",
                                                                    "/static/icons/nav-minus.svg"),
                                    0)),
    children_container_(addWidget(std::make_unique<Wt::WContainerWidget>()))

{
    icon_->addStyleClass("me-1");
    icon_->icon1Clicked().connect(this, &TreeNodeDirW::showNode);
    icon_->icon2Clicked().connect(this, &TreeNodeDirW::closeNode);
    children_container_->addStyleClass("ps-4");
}

void TreeNodeDirW::removeChildNode(TreeNodeW* child) {
    for (auto child_ = children_.begin(); child_ != children_.end(); child_++) {
        if (*child_ == child) {
            children_.erase(child_);
            break;
        }
    }
}

void TreeNodeDirW::performAction(Action action) {
    TreeNodeW::performAction(action);
    switch (action) {
        case Action::EDIT: {
            auto mgr = SessionScopeMap::instance().get()->managers();
            DirectorySptr directory =
                mgr->directory_manager()->get(node_->getNode().resource_id);

            dialog::EditDirectoryDialog* dialog =
                addChild(std::make_unique<dialog::EditDirectoryDialog>(directory));

            dialog->show();

            dialog->directory_updated().connect([=](DirectorySptr directory) {
                text_title_->setText(directory->name);
            });

            dialog->finished().connect([=] {
                removeChild(dialog);
                Wt::log("CreateDirectoryDialog removed");
            });
            break;
        }
    }
}

TreeNodeW* TreeNodeDirW::addChildNode(std::unique_ptr<TreeNodeW> child) {
    TreeNodeW* child_node = children_container_->addWidget(std::move(child));
    child_node->addParent(this);
    children_.push_back(child_node);
    return child_node;
}

std::vector<TreeNodeW*> TreeNodeDirW::getChildrenNodes() {
    return children_;
}

void TreeNodeDirW::open() {
    icon_->	showIcon2();
    showNode();
}

void TreeNodeDirW::showNode() {
    if (getChildrenNodes().empty()) {
        for (auto node_child : node_->getChildren()) {
            auto child_block = addChildNode(this->makeTreeNodeWidget(node_child));
            if (isCanCheck() && check_box_->isChecked()) {
                child_block->checkNode();
            }
        }

    } else {
        for (auto child : getChildrenNodes()) {
            child->setHidden(false);
        }
    }
}

void TreeNodeDirW::closeNode() {
    for (auto child : getChildrenNodes()) {
        child->setHidden(true);
    }
}

void TreeNodeDirW::checkNode() {
    if (!node_->isChecked()) {
        checked_.emit(this);
    }

    check_box_->setChecked(true);

    for (auto child : getChildrenNodes()) {
        child->checkNode();
    }
}

void TreeNodeDirW::uncheckNode() {
    if (node_->isChecked())
        checked_.emit(this);

    uncheckParentNodes();
    for (auto child : getChildrenNodes()) {
        child->uncheckNode();
    }
}

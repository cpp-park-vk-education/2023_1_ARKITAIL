#include "tree_node_dir_w.hpp"

#include <memory>

#include "Wt/WContainerWidget.h"
#include "Wt/WIconPair.h"
#include "Wt/WText.h"
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

void TreeNodeDirW::performAction(Action action) {
    TreeNodeW::performAction(action);
    switch (action) {
        case Action::EDIT: {
            // // (affeeal): каким-то образом мне нужно получить CalendarSptr,
            // // соответствующий данному календарю, который используется
            // // EditCalendarDialog.
            // CalendarSptr dummy_calendar = std::make_shared<Calendar>();

            // dialog::EditCalendarDialog* dialog =
            //     addChild(std::make_unique<dialog::EditCalendarDialog>(dummy_calendar));

            // dialog->show();

            // // dialog.calendar_updated().connect(...);

            // dialog->finished().connect([=] {
            //     removeChild(dialog);
            //     Wt::log("EditCalendarDialog removed");
            // });
            // break;
        }
    }
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

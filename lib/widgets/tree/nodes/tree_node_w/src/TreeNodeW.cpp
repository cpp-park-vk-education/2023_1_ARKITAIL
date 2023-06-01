#include "TreeNodeW.hpp"

#include <Wt/WAnchor.h>
#include <Wt/WBreak.h>
#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WLink.h>
#include <Wt/WPopupWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>
#include <Wt/WText.h>

#include <memory>
#include <string>
#include <vector>

#include "Calendar.hpp"
#include "CreateCalendarDialog.hpp"
#include "Directory.hpp"
#include "EditCalendarDialog.hpp"
#include "ITreeNode.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "OptionsW.hpp"
#include "OptionsWBuilder.hpp"
#include "OptionsWDirector.hpp"
#include "Profile.hpp"
#include "SessionScopeMap.hpp"
#include "TreeNode.hpp"
#include "TreeNodeDirW.hpp"
#include "TreeNodeLeafW.hpp"
#include "TreeNodeW.hpp"
#include "TreeNodeWAnalyst.hpp"
#include "TreeNodeWDirector.hpp"
#include "User.hpp"
#include "Wt/WContainerWidget.h"
#include "Wt/WIconPair.h"
#include "Wt/WText.h"

TreeNodeW::TreeNodeW() :
    Wt::WContainerWidget(),
    node_block_(),
    check_box_container(),
    checked_(),
    text_title_(),
    header_container_(),
    options_button_(),

    analyst_(),
    parent_(),
    node_() {}

TreeNodeW::TreeNodeW(ITreeNode* node) :

    Wt::WContainerWidget(),
    node_block_(),
    check_box_container(),
    check_box_(),
    checked_(),
    text_title_(),
    header_container_(),
    options_button_(),

    analyst_(std::make_unique<TreeNodeWAnalyst>(SessionScopeMap::instance().get()->managers())),
    parent_(nullptr),
    node_(node)

{
    auto node_block = addWidget(std::make_unique<Wt::WContainerWidget>());
    node_block->addStyleClass("p-0");
    node_block_ = node_block->setLayout(std::make_unique<Wt::WHBoxLayout>());
    check_box_container = node_block_->addWidget(std::make_unique<Wt::WContainerWidget>());
    check_box_container->addStyleClass("my-auto mx-0 px-0");
    header_container_ = node_block_->addWidget(std::make_unique<Wt::WContainerWidget>());
}

TreeNodeW* TreeNodeW::addChildNode(std::unique_ptr<TreeNodeW> child) {
    return this;
}

void TreeNodeW::open() {}

void TreeNodeW::showNode() {}

void TreeNodeW::closeNode() {}

std::vector<TreeNodeW*> TreeNodeW::getChildrenNodes() {
    return std::vector<TreeNodeW*>();
}

void TreeNodeW::performAction(Action action) {
    OptionsWBuilder options_builder;
    auto mgr = SessionScopeMap::instance().get()->managers();
    switch (action) {
        case Action::REMOVE:
            mgr->node_manager()->remove(node_->getNode().id);
            removeNode();
            break;

        case Action::SUBSCRIBE:
            mgr->node_manager()->subscribe(node_->getNode().id);
            if (mgr->node_manager()->subscribed(node_->getNode().id)) {
                setOptions(OptionsWDirector().createOptionsUnsubscriptionW(options_builder));
            }
            break;

        case Action::UNSUBSCRIBE:
            mgr->node_manager()->unsubscribe(node_->getNode().id);
            if (!mgr->node_manager()->subscribed(node_->getNode().id)) {
                if (!isRoot() &&
                    node_->getParent()->getNode().type & NodeType::SUBSCRIPTIONS_GROUP) {
                    this->removeNode();
                } else {
                    setOptions(OptionsWDirector().createOptionsSubscriptionW(options_builder));
                }
            }
            break;

        case Action::ADD_CALENDAR: {
            dialog::CreateCalendarDialog* dialog =
                addChild(std::make_unique<dialog::CreateCalendarDialog>(node_));

            dialog->show();

            dialog->node_created().connect([=](Node node) {
                auto tree_node = node_->addChild(node);
                addChildNode(makeTreeNodeWidget(tree_node));
            });

            dialog->finished().connect([=]() {
                removeChild(dialog);
                Wt::log("CreateCalendarDialog removed");
            });
            break;
        }

        case Action::ADD_DIRECTORY:
            // добавить директорию
            break;
    }
}

void TreeNodeW::removeNode() {
    node_->remove();
    parent()->removeWidget(this);
    parent_->removeChildNode(this);
}

void TreeNodeW::removeChildNode(TreeNodeW* child) {}

TreeNodeW* TreeNodeW::addParent(TreeNodeW* parent) {
    parent_ = parent;
    return this;
}

bool TreeNodeW::isRoot() {
    return !parent_;
}

bool TreeNodeW::isCanCheck() {
    return check_box_container->count();
}

bool TreeNodeW::isCheck() {
    if (isCanCheck()) {
        return check_box_->isChecked();
    }
    return false;
}

ITreeNode* TreeNodeW::getTreeNode() {
    return node_;
}

void TreeNodeW::uncheckParentNodes() {
    check_box_->setChecked(false);
    if (!isRoot() && parent_->isCanCheck()) {
        parent_->uncheckParentNodes();
    }
}

void TreeNodeW::addToolTipSignal() {
    tool_tip_->setTransient(true, 2);
    tool_tip_->setAnchorWidget(header_container_);
    header_container_->mouseWentOver().connect([=]() {  // mouseWentOver        
        tool_tip_->setOffsets(Wt::WLength("100px"), Wt::WFlags(Wt::Side::Bottom));
        tool_tip_->setHidden(false);
    });
}

NodeType TreeNodeW::getType() {
    return node_->getNode().type;
}

void TreeNodeW::setOptions(std::unique_ptr<OptionsW> options) {
    options->selectedOption().connect(this, &TreeNodeW::performAction);
    options_button_->setMenu(std::make_unique<OptionsW>());

    options_button_->setMenu(std::move(options));
    options_button_->toggleStyleClass("dropdown-toggle", false);
}

std::unique_ptr<TreeNodeW> TreeNodeW::makeTreeNodeWidget(ITreeNode* tree_node) {
    return TreeNodeWDirector().fillNode(analyst_->analyseTreeNodeWChild(tree_node));
}

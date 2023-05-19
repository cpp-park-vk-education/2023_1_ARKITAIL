#include "tree_node_w.hpp"

#include <Wt/WAnchor.h>
#include <Wt/WBreak.h>
#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WLink.h>
#include <Wt/WPopupWidget.h>
#include <Wt/WPushButton.h>

#include <memory>
#include <string>
#include <vector>

#include "Calendar.hpp"
#include "Directory.hpp"
#include "ITreeNode.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "Profile.hpp"
#include "User.hpp"
#include "in_place_edit_title.hpp"
#include "options_w.hpp"
#include "tree_node_dir_w.hpp"
#include "tree_node_leaf_w.hpp"
#include "tree_node_other_dir_w.hpp"
#include "tree_node_subscriptions_dir_w.hpp"
#include "tree_node_w_builder.hpp"

TreeNodeW::TreeNodeW(ITreeNode* node) :
    Wt::WContainerWidget(),
    parent_(nullptr),
    node_(node) {
    auto node_block = addWidget(std::make_unique<Wt::WContainerWidget>());
    node_block->addStyleClass("p-0");
    node_block_ = node_block->setLayout(std::make_unique<Wt::WHBoxLayout>());
}

TreeNodeW* TreeNodeW::addChildNode(std::unique_ptr<TreeNodeW> child) {
    return this;
}

void TreeNodeW::removeNode() {
    this->clear();
}

void TreeNodeW::addParent(TreeNodeW* parent) {
    parent_ = parent;
}

bool TreeNodeW::isRoot() {
    return this == parent_;
}

void TreeNodeW::uncheckParentNodes() {
    check_box_->setChecked(false);
    if (!parent_->isRoot()) {
        parent_->uncheckParentNodes();
    }
}

std::unique_ptr<TreeNodeW> TreeNodeW::makeTreeNodeWidget(ITreeNode* tree_node) {
    std::unique_ptr<TreeNodeW> res;
    Node node = tree_node->getNode();
    std::vector<std::string> tags;

    if (node.type & (NodeType::PRIVATE_CALENDAR | NodeType::PUBLIC_CALENDAR)) {
        Calendar child = Managers::instance().calendar_manager->get(node.resource_id);
        auto options = std::make_unique<OptionsW>();
        options.get()
            ->addOptionEdit()
            ->addOptionRemove()
            ->addOptionAddCalendar()
            ->addOptionAddDirectory();
        res.get()
            ->addHead(std::make_unique<Wt::WText>(child.name))
            ->addOptions(std::move(options))
            ->addToolTip(child.description, tags);
        return TreeNodeWBuilder()
            .createTreeNodeLeafW(tree_node)
            ->addHead(std::make_unique<Wt::WText>(child.name))
            ->addOptions(std::move(options))
            ->addToolTip(child.description, tags)
            ->addParent(this)
            ->endNode()
            ->getTreeNodeW();

    } else if (node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY)) {
        Directory child = Managers::instance().directory_manager->get(node.resource_id);
        res = std::make_unique<TreeNodeDirW>(tree_node);
        auto options = std::make_unique<OptionsW>();
        options.get()
            ->addOptionEdit()
            ->addOptionRemove()
            ->addOptionAddCalendar()
            ->addOptionAddDirectory();
        res.get()
            ->addHead(std::make_unique<Wt::WText>(child.name))
            ->addOptions(std::move(options))
            ->addToolTip(child.description, tags);

    } else if (node.type & (NodeType::ROOT | NodeType::PRIVATE_GROUP | NodeType::PUBLIC_GROUP)) {
        Directory child = Managers::instance().directory_manager->get(node.resource_id);
        res = std::make_unique<TreeNodeDirW>(tree_node);
        res.get()->addHead(std::make_unique<Wt::WText>(child.name));

    } else if (node.type & (NodeType::PROFILE_GROUP)) {
        // Profile child = Managers::instance().->get(node.resource_id);
        // res = std::make_unique<TreeNodeDirW>( tree_node);
        // res.get()->addHead(std::make_unique<Wt::WText>(child.name));

    } else if (node.type & NodeType::SUBSCRIPTIONS_GROUP) {
        Directory child = Managers::instance().directory_manager->get(node.resource_id);
        res = std::make_unique<TreeNodeSubscriptionsDirW>(tree_node);

    } else if (node.type & NodeType::PROFILE) {
        // res = std::make_unique<TreeNodeProfileW>(tree_node);
        // res.get()->addHead(std::make_unique<InPlaceEditTitle>(child.name));
    }
    res.get()->endNode()->addParent(this);
    return res;
}

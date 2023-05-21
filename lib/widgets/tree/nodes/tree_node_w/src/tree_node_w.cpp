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
#include "SessionScopeMap.hpp"
#include "User.hpp"
#include "in_place_edit_title.hpp"
#include "options_w.hpp"
#include "options_w_builder.hpp"
#include "options_w_director.hpp"
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

//

TreeNodeW* TreeNodeW::addHead(std::unique_ptr<Wt::WWidget> head) {
    header_container_ = node_block_->addWidget(std::make_unique<Wt::WContainerWidget>());
    header_container_->addWidget(std::move(head));
    return this;
}

TreeNodeW* TreeNodeW::addCheckBox() {
    check_box_container = node_block_->addWidget(std::make_unique<Wt::WContainerWidget>());
    check_box_container->addStyleClass("my-auto");
    check_box_ = check_box_container->addWidget(std::make_unique<Wt::WCheckBox>());
    check_box_->checked().connect(this, &TreeNodeW::checkNode);
    check_box_->unChecked().connect(this, &TreeNodeW::uncheckNode);
    return this;
}

TreeNodeW* TreeNodeW::addOptions(std::unique_ptr<OptionsW> options) {
    options_button_ = node_block_->addWidget(std::make_unique<Wt::WPushButton>("•••"));
    options_button_->addStyleClass("p-1 py-0 border-0 btn-light");
    options.get()->selectedOption().connect([=] {
        std::cout << "\nclick option\n";
    });
    options_button_->setMenu(std::move(options));
    options_button_->toggleStyleClass("dropdown-toggle", false);
    return this;
}

void TreeNodeW::addToolTip(std::unique_ptr<Wt::WContainerWidget> content) {
    tool_tip_ = std::make_unique<Wt::WPopupWidget>(std::move(content));
    tool_tip_->setTransient(false, 5);
    tool_tip_->setAnchorWidget(header_container_);
    header_container_->mouseWentOver().connect([=] {
        tool_tip_->setHidden(false);
    });
}

std::unique_ptr<Wt::WContainerWidget> TreeNodeW::fillToolTipContainer(
    std::unique_ptr<Wt::WContainerWidget> content, std::string description,
    std::vector<std::string> tags) {
    content->setMaximumSize(Wt::WLength(300), Wt::WLength::Auto);
    content->addStyleClass("p-2");

    auto description_ptr = content->addWidget(std::make_unique<Wt::WText>(description));
    description_ptr->addStyleClass("text-center text-break");

    content->addWidget(std::make_unique<Wt::WBreak>());

    for (auto&& tag : tags) {
        auto tag_ptr = content->addWidget(
            std::make_unique<Wt::WAnchor>(Wt::WLink(Wt::LinkType::InternalPath, "/search"), tag));
        tag_ptr->addStyleClass("btn btn-light border-success p-0 px-1 mx-1");
        tag_ptr->clicked().connect([=] {
            std::cout << '\n' << tag_ptr->text().toUTF8() << '\n' << std::endl;
        });
    }
    return content;
}

TreeNodeW* TreeNodeW::addToolTip(std::string description, std::vector<std::string> tags) {
    auto content = std::make_unique<Wt::WContainerWidget>();
    addToolTip(std::move(fillToolTipContainer(std::move(content), description, tags)));
    return this;
}

TreeNodeW* TreeNodeW::addToolTip(std::string description, std::vector<std::string> tags,
                                 User author) {
    auto content = std::make_unique<Wt::WContainerWidget>();

    auto author_ptr = content->addWidget(std::make_unique<Wt::WAnchor>(
        Wt::WLink(Wt::LinkType::InternalPath, "/calendars"), author.nickname));
    author_ptr->setStyleClass("fw-bolder");
    author_ptr->clicked().connect([=] {
        std::cout << author_ptr->text().toUTF8() << std::endl;
    });
    content->addWidget(std::make_unique<Wt::WBreak>());

    addToolTip(std::move(fillToolTipContainer(std::move(content), description, tags)));

    return this;
}
TreeNodeW* TreeNodeW::endNode() {
    node_block_->addStretch(1);
    return this;
}

//

std::unique_ptr<TreeNodeW> TreeNodeW::makeTreeNodeWidget(ITreeNode* tree_node) {
    std::unique_ptr<TreeNodeW> res;
    auto mgr = SessionScopeMap::instance().get()->managers();
    Node node = tree_node->getNode();

    std::vector<std::string> tags;
    OptionsWBuilder options_builder;

    if (node.type & (NodeType::PRIVATE_CALENDAR | NodeType::PUBLIC_CALENDAR)) {
        Calendar child = mgr->calendar_manager()->get(node.resource_id);
        res = std::make_unique<TreeNodeLeafW>(tree_node);
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

    } else if (node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY)) {
        Directory child = mgr->directory_manager()->get(node.resource_id);
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
        Directory child = mgr->directory_manager()->get(node.resource_id);
        res = std::make_unique<TreeNodeDirW>(tree_node);
        res.get()->addHead(std::make_unique<Wt::WText>(child.name));

    } else if (node.type & (NodeType::PROFILE_GROUP)) {
        // Profile child = Managers::instance().->get(node.resource_id);
        // res = std::make_unique<TreeNodeDirW>( tree_node);
        // res.get()->addHead(std::make_unique<Wt::WText>(child.name));

    } else if (node.type & NodeType::SUBSCRIPTIONS_GROUP) {
        // Directory child = mgr->directory_manager()->get(node.resource_id);
        // res = std::make_unique<TreeNodeSubscriptionsDirW>(tree_node);

    } else if (node.type & NodeType::PROFILE) {
        // res = std::make_unique<TreeNodeProfileW>(tree_node);
        // res.get()->addHead(std::make_unique<InPlaceEditTitle>(child.name));
    }
    // res.get()->endNode()->addParent(this);
    std::cout << "children" << std::endl;
    for (auto child : tree_node->getChildren()) {
        std::cout << "child: " << mgr->directory_manager()->get(child->getNode().resource_id).name
                  << std::endl;
        res.get()->addChild(res->makeTreeNodeWidget(child));
    }
    std::cout << "children end" << std::endl;

    return res;
}

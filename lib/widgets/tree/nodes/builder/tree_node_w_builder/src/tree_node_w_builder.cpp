#include "tree_node_w_builder.hpp"

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
#include "tree_node_w.hpp"

TreeNodeWBuilder::TreeNodeWBuilder() :
    tree_node_w() {}

TreeNodeWBuilder* TreeNodeWBuilder::createTreeNodeDirW(ITreeNode* node) {
    // tree_node_w.swap(std::make_unique<TreeNodeDirW>(node));
    return this;
}

TreeNodeWBuilder* TreeNodeWBuilder::createTreeNodeLeafW(ITreeNode* node) {
    // tree_node_w.swap(std::make_unique<TreeNodeLeafW>(node));
    return this;
}

TreeNodeWBuilder* TreeNodeWBuilder::createTreeNodeOtherDirW(ITreeNode* node) {
    // tree_node_w.swap(std::make_unique<TreeNodeOtherDirW>(node));
    return this;
}

TreeNodeWBuilder* TreeNodeWBuilder::createTreeNodeSubscriptionsDirW(ITreeNode* node) {
    // tree_node_w.swap(std::make_unique<TreeNodeSubscriptionsDirW>(node));
    return this;
}

TreeNodeWBuilder* TreeNodeWBuilder::addHead(std::unique_ptr<Wt::WWidget> head) {
    tree_node_w->header_container_ =
        tree_node_w->node_block_->addWidget(std::make_unique<Wt::WContainerWidget>());
    tree_node_w->header_container_->addWidget(std::move(head));
    return this;
}

TreeNodeWBuilder* TreeNodeWBuilder::addCheckBox() {
    tree_node_w->check_box_container =
        tree_node_w->node_block_->addWidget(std::make_unique<Wt::WContainerWidget>());
    tree_node_w->check_box_container->addStyleClass("my-auto");
    tree_node_w->check_box_ =
        tree_node_w->check_box_container->addWidget(std::make_unique<Wt::WCheckBox>());
    tree_node_w->check_box_->checked().connect(tree_node_w.get(), &TreeNodeW::checkNode);
    tree_node_w->check_box_->unChecked().connect(tree_node_w.get(), &TreeNodeW::uncheckNode);
    return this;
}

TreeNodeWBuilder* TreeNodeWBuilder::addOptions(std::unique_ptr<OptionsW> options) {
    tree_node_w->options_button_ =
        tree_node_w->node_block_->addWidget(std::make_unique<Wt::WPushButton>("•••"));
    tree_node_w->options_button_->addStyleClass("p-1 py-0 border-0 btn-light");
    // options.get()->selectedOption().connect([=] { проблема
    //     std::cout << "\nclick option\n";
    // });
    tree_node_w->options_button_->setMenu(std::move(options));
    tree_node_w->options_button_->toggleStyleClass("dropdown-toggle", false);
    return this;
}

TreeNodeWBuilder* TreeNodeWBuilder::addToolTip(std::string description,
                                               std::vector<std::string> tags) {
    auto content = std::make_unique<Wt::WContainerWidget>();
    addToolTip(std::move(fillToolTipContainer(std::move(content), description, tags)));
    return this;
}

TreeNodeWBuilder* TreeNodeWBuilder::addToolTip(std::string description,
                                               std::vector<std::string> tags, User author) {
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

TreeNodeWBuilder* TreeNodeWBuilder::addParent(TreeNodeW* parent_node) {
    tree_node_w->parent_ = parent_node;
    return this;
}

TreeNodeWBuilder* TreeNodeWBuilder::endNode() {
    tree_node_w->node_block_->addStretch(1);
    return this;
}

std::unique_ptr<Wt::WContainerWidget> TreeNodeWBuilder::fillToolTipContainer(
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

void TreeNodeWBuilder::addToolTip(std::unique_ptr<Wt::WContainerWidget> content) {
    tree_node_w->tool_tip_ = std::make_unique<Wt::WPopupWidget>(std::move(content));
    tree_node_w->tool_tip_->setTransient(false, 5);
    tree_node_w->tool_tip_->setAnchorWidget(tree_node_w->header_container_);
    tree_node_w->header_container_->mouseWentOver().connect([=] {
        tree_node_w->tool_tip_->setHidden(false);
    });
}

std::unique_ptr<TreeNodeW> TreeNodeWBuilder::getTreeNodeW() {
    return std::move(tree_node_w);
}

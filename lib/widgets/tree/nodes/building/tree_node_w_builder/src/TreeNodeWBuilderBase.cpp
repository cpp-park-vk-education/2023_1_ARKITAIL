#include "TreeNodeWBuilderBase.hpp"

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

#include "ConnectionPoint.hpp"
#include "ITreeNode.hpp"
#include "InPlaceEditTitle.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "OptionsW.hpp"
#include "Profile.hpp"
#include "SessionScopeMap.hpp"
#include "Tag.hpp"
#include "TagW.hpp"
#include "TreeNodeW.hpp"
#include "TreeNodeWAnalyst.hpp"
#include "TreeNodeWAnalystBase.hpp"
#include "TreeW.hpp"
#include "User.hpp"

TreeNodeWBuilderBase* TreeNodeWBuilderBase::addAnalyst(
    std::unique_ptr<TreeNodeWAnalystBase> analyst) {
    tree_node_w->analyst_ = (std::move(analyst));
    return this;
}

TreeNodeWBuilderBase* TreeNodeWBuilderBase::addHead(std::unique_ptr<Wt::WWidget> head) {
    tree_node_w->header_container_->addWidget(std::move(head));
    return this;
}

TreeNodeWBuilderBase* TreeNodeWBuilderBase::addTextHead(std::unique_ptr<Wt::WText> head) {
    tree_node_w->text_title_ = tree_node_w->header_container_->addWidget(std::move(head));
    return this;
}

TreeNodeWBuilderBase* TreeNodeWBuilderBase::addCheckBox() {
    tree_node_w->check_box_container->addStyleClass("my-auto");
    tree_node_w->check_box_ =
        tree_node_w->check_box_container->addWidget(std::make_unique<Wt::WCheckBox>());
    tree_node_w->check_box_->checked().connect(tree_node_w.get(), &TreeNodeW::checkNode);
    tree_node_w->check_box_->unChecked().connect(tree_node_w.get(), &TreeNodeW::uncheckNode);
    return this;
}

TreeNodeWBuilderBase* TreeNodeWBuilderBase::addCheckBoxConnectionPoint(
    ConnectionPoint<Wt::Signal<ITreeNode*>, TreeW, ITreeNode*>* cp) {
    cp->add_sender(&(tree_node_w->checked_));
    return this;
}

TreeNodeWBuilderBase* TreeNodeWBuilderBase::addOptions(std::unique_ptr<OptionsW> options) {
    tree_node_w->options_button_ =
        tree_node_w->node_block_->addWidget(std::make_unique<Wt::WPushButton>("•••"));
    tree_node_w->options_button_->addStyleClass("p-1 py-0 border-0 btn-light");
    options.get()->selectedOption().connect(tree_node_w.get(), &TreeNodeW::performAction);
    tree_node_w->options_button_->setMenu(std::move(options));
    tree_node_w->options_button_->toggleStyleClass("dropdown-toggle", false);
    return this;
}

TreeNodeWBuilderBase* TreeNodeWBuilderBase::addToolTip(std::string description,
                                                       std::vector<Tag> tags) {
    auto content = std::make_unique<Wt::WContainerWidget>();
    addToolTip(fillToolTipContainer(std::move(content), description, tags));
    return this;
}

TreeNodeWBuilderBase* TreeNodeWBuilderBase::addToolTip(std::string description,
                                                       std::vector<Tag> tags, User author) {
    auto content = std::make_unique<Wt::WContainerWidget>();

    auto author_ptr = content->addWidget(std::make_unique<Wt::WAnchor>(
        Wt::WLink(Wt::LinkType::InternalPath, "/calendars"), author.nickname));
    author_ptr->setStyleClass("fw-bolder");
    author_ptr->clicked().connect([=] {
        std::cout << "кликнули на пользователя " << author_ptr->text().toUTF8() << std::endl;
    });
    content->addWidget(std::make_unique<Wt::WBreak>());

    addToolTip(fillToolTipContainer(std::move(content), description, tags));

    return this;
}

TreeNodeWBuilderBase* TreeNodeWBuilderBase::addParent(TreeNodeW* parent_node) {
    tree_node_w->parent_ = parent_node;
    return this;
}

TreeNodeWBuilderBase* TreeNodeWBuilderBase::endNode() {
    tree_node_w->node_block_->addStretch(1);
    return this;
}

std::unique_ptr<Wt::WContainerWidget> TreeNodeWBuilderBase::fillToolTipContainer(
    std::unique_ptr<Wt::WContainerWidget> content, std::string description, std::vector<Tag> tags) {
    content->setMaximumSize(Wt::WLength(300), Wt::WLength::Auto);
    content->addStyleClass("p-2");

    auto description_ptr = content->addWidget(std::make_unique<Wt::WText>(description));
    description_ptr->addStyleClass("text-center text-break");

    content->addWidget(std::make_unique<Wt::WBreak>());

    for (auto&& tag : tags) {
        auto tag_ptr = content->addWidget(std::make_unique<TagW>(tag));
    }
    return content;
}

void TreeNodeWBuilderBase::addToolTip(std::unique_ptr<Wt::WContainerWidget> content) {
    tree_node_w->tool_tip_ = std::make_unique<Wt::WPopupWidget>(std::move(content));
    tree_node_w->addToolTipSignal();
}

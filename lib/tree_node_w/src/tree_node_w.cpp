#include "tree_node_w.hpp"

#include <Wt/WAnchor.h>
#include <Wt/WBreak.h>
#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WLink.h>
#include <Wt/WPopupWidget.h>
#include <Wt/WPushButton.h>

#include "Node.hpp"
#include "Tree.hpp"
#include "TreeNode.hpp"
#include "options_w.hpp"

enum OptionsType { PERSONAL_DIR = 0, PERSONAL_CALENDAR, SUBSCRIPTION };

TreeNodeW::TreeNodeW() : parent_(nullptr) {
    auto node_block = addWidget(std::make_unique<Wt::WContainerWidget>());
    node_block->addStyleClass("p-0");
    node_block_ = node_block->setLayout(std::make_unique<Wt::WHBoxLayout>());
    auto check_box_container = node_block_->addWidget(std::make_unique<Wt::WContainerWidget>());
    check_box_container->addStyleClass("my-auto");
    check_box_ = check_box_container->addWidget(std::make_unique<Wt::WCheckBox>());
    check_box_->checked().connect(this, &TreeNodeW::checkNode);
    check_box_->unChecked().connect(this, &TreeNodeW::uncheckNode);
}

TreeNodeW* TreeNodeW::addOptions(std::unique_ptr<OptionsW> options) {
    options_button_ = node_block_->addWidget(std::make_unique<Wt::WPushButton>("•••"));
    options_button_->addStyleClass("p-1 py-0 border-0 btn-light");
    options.get()->selectedOption().connect([=] { std::cout << "\nytyt\n"; });
    options_button_->setMenu(std::move(options));
    options_button_->toggleStyleClass("dropdown-toggle", false);
    return this;
}

void TreeNodeW::addToolTip(std::unique_ptr<Wt::WContainerWidget> content) {
    tool_tip_ = std::make_unique<Wt::WPopupWidget>(std::move(content));
    tool_tip_->setTransient(false, 5);
    tool_tip_->setAnchorWidget(getTitle());
    getTitle()->mouseWentOver().connect([=] { tool_tip_->setHidden(false); });
}

std::unique_ptr<Wt::WContainerWidget> TreeNodeW::fillToolTipContainer(std::unique_ptr<Wt::WContainerWidget> content,
                                                                      std::string description,
                                                                      std::vector<std::string> tags) {
    content->setMaximumSize(Wt::WLength(300), Wt::WLength::Auto);
    content->addStyleClass("p-2");

    auto description_ptr = content->addWidget(std::make_unique<Wt::WText>(description));
    description_ptr->addStyleClass("text-center text-break");

    content->addWidget(std::make_unique<Wt::WBreak>());

    for (auto&& tag : tags) {
        auto tag_ptr =
            content->addWidget(std::make_unique<Wt::WAnchor>(Wt::WLink(Wt::LinkType::InternalPath, "/search"), tag));
        tag_ptr->addStyleClass("btn btn-light border-success p-0 px-1 mx-1");
        tag_ptr->clicked().connect([=] { std::cout << '\n' << tag_ptr->text().toUTF8() << '\n' << std::endl; });
    }
    return content;
}

TreeNodeW* TreeNodeW::addToolTip(std::string description, std::vector<std::string> tags) {
    auto content = std::make_unique<Wt::WContainerWidget>();
    addToolTip(std::move(fillToolTipContainer(std::move(content), description, tags)));
    return this;
}

TreeNodeW* TreeNodeW::addToolTip(std::string description, std::vector<std::string> tags, std::string author) {
    auto content = std::make_unique<Wt::WContainerWidget>();

    auto author_ptr =
        content->addWidget(std::make_unique<Wt::WAnchor>(Wt::WLink(Wt::LinkType::InternalPath, "/calendars"), author));
    author_ptr->setStyleClass("fw-bolder");
    author_ptr->clicked().connect([=] { std::cout << author_ptr->text().toUTF8() << std::endl; });
    content->addWidget(std::make_unique<Wt::WBreak>());

    addToolTip(std::move(fillToolTipContainer(std::move(content), description, tags)));

    return this;
}
TreeNode* addNode(const Node& node) {
    // node_ = node;
}

TreeNodeW* TreeNodeW::endNode() {
    node_block_->addStretch(1);
    return this;
}

void TreeNodeW::removeNode() { this->clear(); }

void TreeNodeW::addParent(TreeNodeW* parent) { parent_ = parent; }

bool TreeNodeW::isRoot() { return !parent_; }

void TreeNodeW::uncheckParentNodes() {
    check_box_->setChecked(false);
    if (!parent_->isRoot()) {
        parent_->uncheckParentNodes();
    }
}

TreeNodeW* TreeNodeW::hideCheckBox() {
    check_box_->setHidden(true);
    return this;
}
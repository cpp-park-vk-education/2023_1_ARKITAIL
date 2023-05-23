#include "tree_node_w.hpp"

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
#include "tree_node_w_analyst.hpp"
#include "tree_node_w_builder_base.hpp"
#include "tree_node_w_director.hpp"

TreeNodeW::TreeNodeW() {}

TreeNodeW::TreeNodeW(ITreeNode* node) :
    Wt::WContainerWidget(),
    parent_(nullptr),
    node_(node) {
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

void TreeNodeW::checkNode() {}
void TreeNodeW::uncheckNode() {}
void TreeNodeW::showNode() {}
void TreeNodeW::closeNode() {}

void TreeNodeW::performAction(Action action) {
    OptionsWBuilder options_builder;
    switch (action) {
        case Action::REMOVE:
            removeNode();
            break;

        case Action::EDIT: {
            // (affeeal): каким-то образом мне нужно получить CalendarSptr,
            // соответствующий данному календарю, который используется
            // EditCalendarDialog.
            CalendarSptr dummy_calendar = std::make_shared<Calendar>();

            dialog::EditCalendarDialog* dialog = addChild(
                std::make_unique<dialog::EditCalendarDialog>(dummy_calendar));

            dialog->show();

            // dialog.calendar_updated().connect(...);

            dialog->finished().connect([=] {
              removeChild(dialog);
              Wt::log("EditCalendarDialog removed");
            });
            break;
        }

        case Action::SUBSCRIBE:
            setOptions(OptionsWDirector().createOptionsUnsubscriptionW(options_builder));
            break;

        case Action::UNSUBSCRIBE:
            //нужна проверка в чьем это календаре
            setOptions(OptionsWDirector().createOptionsSubscriptionW(options_builder));
            this->removeNode();  //в своем - удаление, в чужом - смена опций
            break;

        case Action::ADD_CALENDAR: {
            dialog::CreateCalendarDialog* dialog
              = addChild(std::make_unique<dialog::CreateCalendarDialog>());

            dialog->show();

            // dialog.calendar_created().connect(...);

            dialog->finished().connect([=] {
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
    this->clear();
}

TreeNodeW* TreeNodeW::addParent(TreeNodeW* parent) {
    parent_ = parent;
    return this;
}

bool TreeNodeW::isRoot() {
    return this == parent_;
}

bool TreeNodeW::isCanCheck() {
    return check_box_container->count();
}

void TreeNodeW::uncheckParentNodes() {
    check_box_->setChecked(false);
    if (parent_->isCanCheck()) {
        parent_->uncheckParentNodes();
    }
}

void TreeNodeW::addToolTipSignal() {
    tool_tip_->setTransient(false, 5);
    tool_tip_->setAnchorWidget(header_container_);
    header_container_->mouseWentOver().connect([=] {
        tool_tip_->setHidden(false);
        std::cout << "открыли тултип\n" << std::endl;
    });
}

NodeType TreeNodeW::getType() {
    return node_->getNode().type;
}

TreeNodeW* TreeNodeW::addHead(std::unique_ptr<Wt::WWidget> head) {
    header_container_->addWidget(std::move(head));
    return this;
}

TreeNodeW* TreeNodeW::addCheckBox() {
    check_box_ = check_box_container->addWidget(std::make_unique<Wt::WCheckBox>());
    check_box_->checked().connect(this, &TreeNodeW::checkNode);
    check_box_->unChecked().connect(this, &TreeNodeW::uncheckNode);
    return this;
}

TreeNodeW* TreeNodeW::addOptions(std::unique_ptr<OptionsW> options) {
    options_button_ = node_block_->addWidget(std::make_unique<Wt::WPushButton>("•••"));
    options_button_->addStyleClass("p-1 py-0 border-0 btn-light");
    options.get()->selectedOption().connect(this, &TreeNodeW::performAction);
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
        std::cout << "открыли тултип\n" << std::endl;
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

void TreeNodeW::setOptions(std::unique_ptr<OptionsW> options) {
    options.get()->selectedOption().connect(this, &TreeNodeW::performAction);
    options_button_->setMenu(std::move(options));
}

std::unique_ptr<TreeNodeW> TreeNodeW::makeTreeNodeWidget(ITreeNode* tree_node) {
    auto mgr = SessionScopeMap::instance().get()->managers();
    std::unique_ptr<TreeNodeW> res;

    Node node = tree_node->getNode();
    std::vector<std::string> tags;
    tags.push_back("tag1");
    OptionsWBuilder options_builder;
    if ((node.type & (NodeType::PUBLIC_DIRECTORY | NodeType::PUBLIC_CALENDAR)) &&
        (this->getType() & NodeType::SUBSCRIPTIONS_GROUP)) {
        Directory child = mgr->directory_manager()->get(node.resource_id);
        res = std::make_unique<TreeNodeSubscriptionsDirW>(tree_node);
        res.get()
            ->addCheckBox()
            ->addHead(std::make_unique<Wt::WText>(child.name))
            ->addOptions(OptionsWDirector().createOptionsUnsubscriptionW(options_builder))
            ->endNode();
        // return TreeNodeSubDirWBuilder()
        //     .createTreeNodeW(tree_node)
        //     ->addHead(std::make_unique<Wt::WText>(child.name))
        //     ->addParent(this)
        //     ->endNode()
        //     ->getTreeNodeW();
        // Directory child = mgr->directory_manager()->get(node.resource_id);
        // res = std::make_unique<TreeNodeSubscriptionsDirW>(tree_node);

    } else if (node.type & (NodeType::PRIVATE_CALENDAR | NodeType::PUBLIC_CALENDAR)) {
        CalendarSptr child = mgr->calendar_manager()->get(node.resource_id);
        res = std::make_unique<TreeNodeLeafW>(tree_node);
        res.get()
            ->addHead(std::make_unique<Wt::WText>(child->summary))
            ->addCheckBox()
            ->addOptions(OptionsWDirector().createOptionsPersonalCalendarW(options_builder))
            ->addToolTip(child->description, tags)
            ->endNode();
        ;
        // return TreeNodeLeafWBuilder()
        //     .createTreeNodeW(tree_node)
        //     ->addHead(std::make_unique<Wt::WText>(child.name))
        //     ->addOptions(OptionsWDirector().createOptionsPersonalCalendarW(options_builder))
        //     ->addToolTip(child.description, tags)
        //     ->addParent(this)
        //     ->endNode()
        //     ->getTreeNodeW();

    } else if (node.type & (NodeType::PRIVATE_DIRECTORY | NodeType::PUBLIC_DIRECTORY)) {
        Directory child = mgr->directory_manager()->get(node.resource_id);
        res =
            TreeNodeWDirector().createNode(TreeNodeWAnalyst().analyseTreeNodeDirWChild(tree_node));
        // res = TreeNodeDirWBuilder()
        //           .createTreeNodeW(tree_node)
        //           ->addHead(std::make_unique<Wt::WText>(child.name))
        //           ->addCheckBox()
        //           ->addOptions(OptionsWDirector().createOptionsCalendarsDirW(options_builder))
        //           ->addToolTip(child.description, tags)
        //           ->endNode()
        //           ->getTreeNodeW();

    } else if (node.type & (NodeType::ROOT | NodeType::PRIVATE_GROUP | NodeType::PUBLIC_GROUP |
                            NodeType::SUBSCRIPTIONS_GROUP)) {
        Directory child = mgr->directory_manager()->get(node.resource_id);

        res = TreeNodeDirWBuilder()
                  .createTreeNodeW(tree_node)
                  ->addHead(std::make_unique<Wt::WText>(child.name))
                  ->endNode()
                  ->getTreeNodeW();

    } else if (node.type & (NodeType::PROFILE_GROUP)) {
        Directory child = mgr->directory_manager()->get(node.resource_id);
        res = TreeNodeDirWBuilder()
                  .createTreeNodeW(tree_node)
                  ->addHead(std::make_unique<Wt::WText>(child.name))
                  ->endNode()
                  ->getTreeNodeW();

    } else if (node.type & NodeType::PROFILE) {
        // Profile child = Managers::instance().profile_manager->get(node.resource_id);
        // return TreeNodeOtherDirWBuilder()
        //     .createTreeNodeW(tree_node)
        //     ->addHead(std::make_unique<InPlaceEditTitle>(child.name))
        //     ->addParent(this)
        //     ->endNode()
        //     ->getTreeNodeW();
    }

    return res;
}

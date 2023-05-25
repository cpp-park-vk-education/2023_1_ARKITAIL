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
#include "TreeNodeWAnalyst.hpp"
#include "User.hpp"
#include "Wt/WContainerWidget.h"
#include "Wt/WIconPair.h"
#include "Wt/WText.h"
#include "options_w.hpp"
#include "options_w_builder.hpp"
#include "options_w_director.hpp"
#include "tree_node_dir_w.hpp"
#include "tree_node_leaf_w.hpp"
#include "tree_node_w.hpp"
#include "tree_node_w_director.hpp"

TreeNodeW::TreeNodeW() {}

TreeNodeW::TreeNodeW(ITreeNode* node) :
    Wt::WContainerWidget(),
    parent_(nullptr),
    node_(node),
    analyst_(std::make_unique<TreeNodeWAnalyst>()) {
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
            // node_->remove();
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
    // node_->remove();
    parent()->removeWidget(this);
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
    tool_tip_->setTransient(true, 2);
    tool_tip_->setAnchorWidget(header_container_);
    header_container_->clicked().connect([=] {  // mouseWentOver
        tool_tip_->setOffsets(Wt::WLength("100px"), Wt::WFlags(Wt::Side::Bottom));
        tool_tip_->setHidden(false);
    });
}

NodeType TreeNodeW::getType() {
    return node_->getNode().type;
}

void TreeNodeW::setOptions(std::unique_ptr<OptionsW> options) {
    options->selectedOption().connect(this, &TreeNodeW::performAction);
    options_button_->setMenu(std::move(options));
}

std::unique_ptr<TreeNodeW> TreeNodeW::makeTreeNodeWidget(ITreeNode* tree_node) {
    return TreeNodeWDirector().fillNode(analyst_->analyseTreeNodeWChild(tree_node));
}

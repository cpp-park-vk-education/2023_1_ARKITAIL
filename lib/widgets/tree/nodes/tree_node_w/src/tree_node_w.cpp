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
#include "Wt/WContainerWidget.h"
#include "Wt/WIconPair.h"
#include "Wt/WText.h"
#include "in_place_edit_title.hpp"
#include "options_w.hpp"
#include "options_w_builder.hpp"
#include "options_w_director.hpp"
#include "tree_node_dir_w.hpp"
#include "tree_node_leaf_w.hpp"
#include "tree_node_other_dir_w.hpp"
#include "tree_node_subscriptions_dir_w.hpp"
#include "tree_node_w.hpp"
#include "tree_node_w_analyst.hpp"
#include "tree_node_w_builder.hpp"
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

        case Action::EDIT:
            // редактирование
            break;

        case Action::SUBSCRIBE:
            setOptions(OptionsWDirector().createOptionsUnsubscriptionW(options_builder));
            break;

        case Action::UNSUBSCRIBE:
            //нужна проверка в чьем это календаре
            setOptions(OptionsWDirector().createOptionsSubscriptionW(options_builder));
            this->removeNode();  //в своем - удаление, в чужом - смена опций
            break;

        case Action::ADD_CALENDAR:
            // добавить календарь
            break;

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
    header_container_->mouseWentOver().connect([=](Wt::WMouseEvent mouse) {
        std::cout << "\n координаты" << mouse.widget().x << mouse.widget().y << std::endl;
        tool_tip_->setOffsets(Wt::WLength("100px"), Wt::WFlags(Wt::Side::Bottom));
        tool_tip_->setHidden(false);
        std::cout << "открыли тултип\n" << std::endl;
    });
}

NodeType TreeNodeW::getType() {
    return node_->getNode().type;
}

void TreeNodeW::setOptions(std::unique_ptr<OptionsW> options) {
    options.get()->selectedOption().connect(this, &TreeNodeW::performAction);
    options_button_->setMenu(std::move(options));
}

std::unique_ptr<TreeNodeW> TreeNodeW::makeTreeNodeWidget(ITreeNode* tree_node) {
    auto data = TreeNodeWAnalyst().analyseTreeNodeDirWChild(tree_node);
    std::unique_ptr<TreeNodeW> tree_node_w;

    if (data.components_set & Components::TYPE_DIR) {
        tree_node_w = std::make_unique<TreeNodeDirW>(data.tree_node);
    } else if (data.components_set & Components::TYPE_OTHER_DIR) {
        tree_node_w = std::make_unique<TreeNodeOtherDirW>(data.tree_node);
    } else if (data.components_set & Components::TYPE_SUB_DIR) {
        tree_node_w = std::make_unique<TreeNodeSubscriptionsDirW>(data.tree_node);
    } else {
        tree_node_w = std::make_unique<TreeNodeLeafW>(data.tree_node);
    }
    std::cout << (data.components_set & Components::TYPE_DIR) << " "
              << (data.components_set & Components::TYPE_OTHER_DIR) << " "
              << (data.components_set & Components::TYPE_SUB_DIR) << '\n';

    auto node_builder = TreeNodeWBuilder(std::move(tree_node_w));

    return TreeNodeWDirector().fillNode(data, node_builder);
}

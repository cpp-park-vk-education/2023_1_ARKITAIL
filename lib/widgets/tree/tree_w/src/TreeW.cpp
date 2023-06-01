#include "TreeW.hpp"

#include <Wt/WAnimation.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WDateTime.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLogger.h>
#include <Wt/WPushButton.h>
#include <Wt/WTime.h>

#include <algorithm>
#include <memory>
#include <string>

#include "ITreeNode.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "Tree.hpp"
#include "TreeNode.hpp"
#include "TreeNodeDirW.hpp"
#include "TreeNodeLeafW.hpp"
#include "TreeNodeWAnalyst.hpp"
#include "TreeNodeWDirector.hpp"
#include "TreeNodeWOtherAnalyst.hpp"

TreeW::TreeW() :
    tree_manager_(),
    search_line_(),
    remember_combination_button_(),
    root_() {
    animateHide(Wt::WAnimation(Wt::AnimationEffect::SlideInFromLeft));
    setStyleClass("start-0 w-100");
    auto tree_header_container = addWidget(std::make_unique<Wt::WContainerWidget>());
    auto tree_header = tree_header_container->setLayout(std::make_unique<Wt::WHBoxLayout>());
    search_line_ = tree_header->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
    search_line_->setPlaceholderText("Введите название календаря...");
    search_line_->setStyleClass("form-control");
    search_line_->setWidth(Wt::WLength(250));
    remember_combination_button_ =
        tree_header->addWidget(std::make_unique<Wt::WPushButton>(Wt::WString("Запомнить")));
    remember_combination_button_->setStyleClass("btn");
    remember_combination_button_->setEnabled(false);
    remember_combination_button_->setWidth(Wt::WLength(120));

    search_line_->enterPressed().connect(this, &TreeW::search);
    remember_combination_button_->clicked().connect(this, &TreeW::rememberCombination);
}

void TreeW::setRoot(const Node& node) {
    if (root_) {
        removeChild(root_);
    }
    auto mgr = SessionScopeMap::instance().get()->managers();

    tree_manager_ = std::make_unique<Tree>(node);

    auto tree_node = tree_manager_->getRoot();

    if (node.type & NodeType::ROOT) {
        root_ = addWidget(
            TreeNodeWDirector().fillNode(TreeNodeWAnalyst(mgr).analyseTreeNodeWChild(tree_node)));
    } else {
        root_ = addWidget(TreeNodeWDirector().fillNode(
            TreeNodeWOtherAnalyst(mgr).analyseTreeNodeWChild(tree_node)));
    }
}

void TreeW::rememberCombination() {}

void TreeW::search() {}

void TreeW::checkNode(ITreeNode* tree_node) {
    if (tree_node->isChecked()) {
        tree_manager_->uncheckNode(tree_node);
    } else {
        tree_manager_->checkNode(tree_node);
    }
    std::cout << "\nnode_checked из дерева => выпущен сигнал в хедер\n" << std::endl;
    node_checked.emit();
}

void TreeW::getRangeEvents(Wt::WDate date1, Wt::WDate date2) {
    auto events = tree_manager_->getCheckedEventsByInterval(
        Wt::WDateTime(date1, Wt::WTime(0, 0, 0)), Wt::WDateTime(date2, Wt::WTime(0, 0, 0)));
    std::cout << events.size() << "\n";
    for (auto e : events) {
        std::cout << e.summary << std::endl;
    }

    std::cout << "\nпо двум датам получили события и отправили в тело календаря\n" << std::endl;
    events_getted.emit(date1, events);
}

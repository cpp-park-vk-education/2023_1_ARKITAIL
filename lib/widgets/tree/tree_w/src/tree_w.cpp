#include "tree_w.hpp"

#include <Wt/WAnimation.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

#include <algorithm>
#include <memory>
#include <string>

#include "ITreeNode.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "Tree.hpp"
#include "TreeNode.hpp"
#include "tree_node_dir_w.hpp"
#include "tree_node_leaf_w.hpp"
#include "tree_node_other_dir_w.hpp"

TreeW::TreeW()
// Прописать список инициализации для полей
{
    // Анимация?
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
    auto mgr = SessionScopeMap::instance().get()->managers();
    tree_manager_ = std::make_unique<Tree>(node);
    root_ = new TreeNodeDirW(tree_manager_->getRoot());

    auto tree_node = tree_manager_->getRoot();
    std::cout << tree_node << std::endl;

    auto root = root_->makeTreeNodeWidget(tree_node);

    if (node.type & NodeType::PUBLIC_CALENDAR) {
        auto calendar = mgr->calendar_manager()->get(node.resource_id);
        root_ = addWidget(std::move(root));

    } else {
        auto directory = mgr->directory_manager()->get(node.resource_id);
        if (node.type & NodeType::ROOT) {
            root_ = addWidget(std::move(root));
        } else {
            root_ = addWidget(std::move(root));
        }
    }
}

void TreeW::rememberCombination() {}

void TreeW::search() {}

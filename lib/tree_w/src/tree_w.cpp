#include "tree_w.hpp"

#include <Wt/WAnimation.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

#include <memory>

#include "Node.hpp"
#include "Tree.hpp"
#include "TreeNode.hpp"
#include "options_calendars_dir_w.hpp"
#include "options_personal_calendar_w.hpp"
#include "options_subscription_w.hpp"
#include "tree_node_calendar_w.hpp"
#include "tree_node_dir_w.hpp"
#include "tree_node_other_dir_w.hpp"
#include "tree_node_profile_w.hpp"

TreeW::TreeW() {
    animateHide(Wt::WAnimation(Wt::AnimationEffect::SlideInFromLeft));
    setStyleClass("start-0 w-100");
    auto tree_navbar_container = addWidget(std::make_unique<Wt::WContainerWidget>());
    auto tree_navbar = tree_navbar_container->setLayout(std::make_unique<Wt::WHBoxLayout>());
    auto search_linePtr = std::make_unique<Wt::WLineEdit>();
    search_line_ = search_linePtr.get();
    search_line_->setPlaceholderText("Введите название календаря");
    search_line_->setStyleClass("form-control");
    search_line_->setWidth(Wt::WLength(250));
    tree_navbar->addWidget(std::move(search_linePtr), 1);
    remember_combination_button_ = tree_navbar->addWidget(std::make_unique<Wt::WPushButton>(Wt::WString("Запомнить")));
    remember_combination_button_->setStyleClass("btn");
    remember_combination_button_->setEnabled(false);
    remember_combination_button_->setWidth(Wt::WLength(120));

    options_.push_back(std::make_unique<OptionsCalendarsDirW>());
    options_.push_back(std::make_unique<OptionsPersonalCalendarW>());
    options_.push_back(std::make_unique<OptionsSubscriptionW>());

    search_line_->enterPressed().connect(this, &TreeW::search);
    remember_combination_button_->clicked().connect(this, &TreeW::rememberCombination);
}

void TreeW::setRoot() {
    // передается нода Сени
    // по ней я запрашиваю дерево (вектор из нод)
    // иду по нему и запускаю метод(надо его написать), который проверяет тип ноды
    // если это лист(календарь), то он просто добавляется
    // иначе(директория), то она рисуется и в ее метод передается ее вектор нод, которые добавляются в контейнер нод

    // std::vector<std::string> tags;
    // tags.push_back("tag1");
    // tags.push_back("tag2");
    // tags.push_back("tag3");
    // root_ = addWidget(std::make_unique<TreeNodeDirW>("Календари"))->hideCheckBox()->endNode();
    // auto group = root_->addChildNode(std::make_unique<TreeNodeDirW>("Группировки"))->endNode();
    // group->addChildNode(std::make_unique<TreeNodeProfileW>("ГруппаТупики"))
    //     ->addOptions(std::make_unique<OptionsPersonalCalendarW>())
    //     ->endNode();
    // auto priv = root_->addChildNode(std::make_unique<TreeNodeDirW>("Приватные"))->endNode();
    // auto priv1 = priv->addChildNode(std::make_unique<TreeNodeDirW>("Папка1"))
    //                  ->addOptions(std::make_unique<OptionsCalendarsDirW>())
    //                  ->endNode();
    // priv1->addChildNode(std::make_unique<TreeNodeProfileW>("Прив1"))
    //     ->addOptions(std::make_unique<OptionsPersonalCalendarW>())
    //     ->endNode();
    // priv->addChildNode(std::make_unique<TreeNodeProfileW>("Группа1"))
    //     ->addOptions(std::make_unique<OptionsPersonalCalendarW>())
    //     ->endNode();

    // auto pub = root_->addChildNode(std::make_unique<TreeNodeDirW>("Публичные"))->endNode();
    // pub->addChildNode(std::make_unique<TreeNodeCalendarW>("Публичные тупики"))
    //     ->addOptions(std::make_unique<OptionsPersonalCalendarW>())
    //     ->addToolTip("Календарь с главными событиями тупиков", tags)
    //     ->endNode();
    // auto sub = root_->addChildNode(std::make_unique<TreeNodeDirW>("Подписки"))->endNode();
    // sub->addChildNode(std::make_unique<TreeNodeCalendarW>("МГТУ"))
    //     ->addOptions(std::make_unique<OptionsSubscriptionW>())
    //     ->addToolTip(
    //         "Добро пожаловать на официальную страницу МГТУ им. Н.Э. Баумана! Здесь вы найдете новости "
    //         "нашего университета, анонсы мероприятий и многое другое.",
    //         tags, "МГТУ")
    //     ->endNode();
}

void TreeW::setRoot(Node* node) {
    // tree_manager_ = Tree(node);
    auto tree_node = tree_manager_->getRoot();
    // Node* node = tree_node->getNode();
    // у менеджера дир нужно поле name
    std::string name = "";
    if (node->type & ROOT) {
        root_ = addWidget(std::make_unique<TreeNodeDirW>(name, tree_node));
    } else {
        root_ = addWidget(std::make_unique<TreeNodeOtherDirW>(name, tree_node));
    }
}

void TreeW::rememberCombination() {}

void TreeW::search() {}

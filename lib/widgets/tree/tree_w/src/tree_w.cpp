#include "tree_w.hpp"

#include <Wt/WAnimation.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

#include <memory>
#include <string>

#include "ITreeNode.hpp"
#include "Managers.hpp"
#include "Node.hpp"
#include "SessionScopeMap.hpp"
#include "Tree.hpp"
#include "tree_node_dir_w.hpp"
#include "tree_node_leaf_w.hpp"
#include "tree_node_other_dir_w.hpp"

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
    remember_combination_button_ =
        tree_navbar->addWidget(std::make_unique<Wt::WPushButton>(Wt::WString("Запомнить")));
    remember_combination_button_->setStyleClass("btn");
    remember_combination_button_->setEnabled(false);
    remember_combination_button_->setWidth(Wt::WLength(120));

    search_line_->enterPressed().connect(this, &TreeW::search);
    remember_combination_button_->clicked().connect(this, &TreeW::rememberCombination);
}

void TreeW::setRoot() {
    // передается нода Сени
    // по ней я запрашиваю дерево (вектор из нод)
    // иду по нему и запускаю метод(надо его написать), который проверяет тип ноды
    // если это лист(календарь), то он просто добавляется
    // иначе(директория), то она рисуется и в ее метод передается ее вектор нод, которые добавляются
    // в контейнер нод

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
    //         "Добро пожаловать на официальную страницу МГТУ им. Н.Э. Баумана! Здесь вы найдете
    //         новости " "нашего университета, анонсы мероприятий и многое другое.", tags, "МГТУ")
    //     ->endNode();
}

void TreeW::setRoot(const Node& node) {
    auto mgr = SessionScopeMap::instance().get()->managers();
    std::cout << "12\n" << std::endl;
    tree_manager_ = std::make_unique<Tree>(node);

    auto tree_node = tree_manager_->getRoot();

    if (node.type & NodeType::PUBLIC_CALENDAR) {
        std::cout << "22\n" << std::endl;
        auto calendar = mgr->calendar_manager()->get(node.resource_id);
        std::cout << "33\n" << std::endl;
        root_ = addWidget(root_->makeTreeNodeWidget(tree_node));

    } else {
        auto directory = mgr->directory_manager()->get(node.resource_id);
        if (node.type & NodeType::ROOT) {
            root_ = addWidget(root_->makeTreeNodeWidget(tree_node));
        } else {
            root_ = addWidget(root_->makeTreeNodeWidget(tree_node));
        }
    }
}

void TreeW::rememberCombination() {}

void TreeW::search() {}

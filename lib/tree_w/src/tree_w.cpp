#include "tree_w.hpp"

#include <Wt/WAnimation.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

#include <memory>

#include "options_calendars_dir_w.hpp"
#include "options_personal_calendar_w.hpp"
#include "options_subscription_w.hpp"
#include "options_w.hpp"
#include "tree_node_calendar_w.hpp"
#include "tree_node_calendars_dir_w.hpp"
#include "tree_node_dir_w.hpp"
#include "tree_node_group_w.hpp"

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

    search_line_->enterPressed().connect(this, &TreeW::search);
    remember_combination_button_->clicked().connect(this, &TreeW::rememberCombination);
}

void TreeW::setRoot() {
    // передается нода Сени
    // по ней я запрашиваю дерево (вектор из нод)
    // иду по нему и запускаю метод(надо его написать), который проверяет тип ноды
    // если это лист(календарь), то он просто добавляется
    // иначе(директория), то она рисуется и в ее метод передается ее вектор нод, которые добавляются в контейнер нод
    root_ = addWidget(std::make_unique<TreeNodeDirW>("Календари"))->endNode();
    root_->hideCheckBox();
    auto group = root_->addChildNode(std::make_unique<TreeNodeDirW>("Группировки"))->endNode();
    group->addChildNode(std::make_unique<TreeNodeGroupW>("Тупики"))
        ->addOptions(std::make_unique<OptionsPersonalCalendarW>())
        ->endNode();
    auto priv = root_->addChildNode(std::make_unique<TreeNodeDirW>("Приватные"))->endNode();
    auto priv1 = priv->addChildNode(std::make_unique<TreeNodeDirW>("Папка1"))
                     ->addOptions(std::make_unique<OptionsPersonalCalendarW>())
                     ->endNode();
    priv->addChildNode(std::make_unique<TreeNodeGroupW>("Rfktylfhm"))
        ->addOptions(std::make_unique<OptionsPersonalCalendarW>())
        ->endNode();

    auto pub = root_->addChildNode(std::make_unique<TreeNodeDirW>("Публичные"))->endNode();
    auto sub = root_->addChildNode(std::make_unique<TreeNodeDirW>("Подписки"))->endNode();
}

void TreeW::rememberCombination() {}

void TreeW::search() {}

#include "AddProfileW.hpp"

#include <Wt/WHBoxLayout.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>

#include <vector>

#include "TreeNodeW.hpp"
#include "SessionScopeMap.hpp"
#include "Managers.hpp"
#include "TreeNodeWAnalyst.hpp"
#include "TreeNodeWDirector.hpp"

AddProfileW::AddProfileW(TreeNodeW* profile_group) :
    profile_group_(profile_group) {

    auto layout = setLayout(std::make_unique<Wt::WHBoxLayout>());

    input_name_ = layout->addWidget(std::make_unique<Wt::WLineEdit>(), 1);
    input_name_->setPlaceholderText("Введите название профиля...");
    input_name_->setStyleClass("form-control");
    input_name_->setWidth(Wt::WLength(260));
    input_name_->setMaxLength(30);  // Илья

    remember_combination_button_ =
        layout->addWidget(std::make_unique<Wt::WPushButton>(Wt::WString("Запомнить")));
    remember_combination_button_->setStyleClass("btn");
    remember_combination_button_->setWidth(Wt::WLength(120));
    setButtonEnabled(false);

    remember_combination_button_->clicked().connect(this, &AddProfileW::validate);
}

void AddProfileW::setButtonEnabled(bool value) {
    remember_combination_button_->setEnabled(value);
}

void AddProfileW::validate() {
    if (!input_name_->text().empty()) {
        need_checked_nodes_.emit();
    }
}

void AddProfileW::addProfileW(std::vector<size_t> nodes) {
    auto manager = SessionScopeMap::instance().get()->managers();
    ProfileSptr profile = std::make_shared<Profile>(0, 0, 0, nodes, input_name_->text().toUTF8());

    size_t profile_id = manager->profile_manager()->add(profile, profile_group_->getTreeNode()->getNode().id);
    auto new_profile = manager->profile_manager()->get(profile_id);

    Node node = manager->node_manager()->get(new_profile->node_id);
    auto tree_node = profile_group_->getTreeNode()->addChild(node);

    profile_group_->open();
    profile_group_->addChildNode(TreeNodeWDirector().fillNode(TreeNodeWAnalyst(manager).analyseTreeNodeWChild(tree_node)));

    input_name_->setText("");
}

Wt::Signal<Node*>& AddProfileW::profileAdded() {
    return profile_added_;
}

Wt::Signal<>& AddProfileW::needCheckedNodes() {
    return need_checked_nodes_;
}


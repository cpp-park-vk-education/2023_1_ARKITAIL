#include "AddProfileW.hpp"

#include <Wt/WHBoxLayout.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WString.h>

#include <vector>

#include "TreeNodeW.hpp"
#include "SessionScopeMap.hpp"
#include "Managers.hpp"

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
    auto mgr = SessionScopeMap::instance().get()->managers();

    // profile_group_->addChildNode();
    input_name_->setText("");
}

Wt::Signal<Node*>& AddProfileW::profileAdded() {
    return profile_added_;
}

Wt::Signal<>& AddProfileW::needCheckedNodes() {
    return need_checked_nodes_;
}


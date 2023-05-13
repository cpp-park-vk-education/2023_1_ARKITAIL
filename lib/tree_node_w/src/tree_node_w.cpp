#include "tree_node_w.hpp"

#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPushButton.h>

TreeNodeW::TreeNodeW() {
    auto node_block = addWidget(std::make_unique<Wt::WContainerWidget>());
    node_block->addStyleClass("p-0");
    node_block_ = node_block->setLayout(std::make_unique<Wt::WHBoxLayout>());
    auto check_box_container = node_block_->addWidget(std::make_unique<Wt::WContainerWidget>());
    check_box_container->addStyleClass("my-auto");
    check_box_ = check_box_container->addWidget(std::make_unique<Wt::WCheckBox>());
    check_box_->checked().connect(this, &TreeNodeW::checkNode);
    check_box_->unChecked().connect(this, &TreeNodeW::uncheckNode);
}

TreeNodeW* TreeNodeW::addOptions(std::unique_ptr<Wt::WPopupMenu> options) {
    options_button_ = node_block_->addWidget(std::make_unique<Wt::WPushButton>("•••"));
    options_button_->addStyleClass("p-1 py-0 border-0 btn-light");
    options_button_->setMenu(std::move(options));
    options_button_->toggleStyleClass("dropdown-toggle", false);
    return this;
}

TreeNodeW* TreeNodeW::endNode() {
    node_block_->addStretch(1);
    return this;
}

void TreeNodeW::removeNode() { this->clear(); }

void TreeNodeW::hideCheckBox() { check_box_->setHidden(true); }
#include "tree_node_w.hpp"

#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>

#include "options_w.hpp"

TreeNodeW::TreeNodeW() {
    auto node_block = addWidget(std::make_unique<Wt::WContainerWidget>());
    node_block->addStyleClass("p-0");
    node_block_ = node_block->setLayout(std::make_unique<Wt::WHBoxLayout>());
    check_box_ = node_block_->addWidget(std::make_unique<Wt::WCheckBox>());
    check_box_->setStyleClass("m-1 p-2");
    check_box_->checked().connect(this, &TreeNodeW::checkNode);
    check_box_->unChecked().connect(this, &TreeNodeW::uncheckNode);
}

TreeNodeW* TreeNodeW::addOptions(std::unique_ptr<OptionsW> options) {
    options_ = node_block_->addWidget(std::move(options));
    return this;
}

TreeNodeW* TreeNodeW::endNode() {
    node_block_->addStretch(1);
    return this;
}

void TreeNodeW::removeNode() { this->clear(); }

void TreeNodeW::hideCheckBox() { check_box_->setHidden(true); }
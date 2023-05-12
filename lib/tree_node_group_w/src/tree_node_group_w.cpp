#include "tree_node_group_w.hpp"

#include "Wt/WInPlaceEdit.h"

TreeNodeGroupW::TreeNodeGroupW(std::string label) {
    label_ = node_block_->addWidget(std::make_unique<Wt::WInPlaceEdit>(label));
    label_->addStyleClass("inline-block");
}
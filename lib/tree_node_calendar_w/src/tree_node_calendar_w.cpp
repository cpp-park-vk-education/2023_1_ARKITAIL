#include "tree_node_calendar_w.hpp"

#include <Wt/WString.h>
#include <Wt/WText.h>

TreeNodeCalendarW::TreeNodeCalendarW(std::string label, TreeNode* node) : TreeNodeLeafW(node) {
    label_ = node_block_->addWidget(std::make_unique<Wt::WText>(label));
}

Wt::WInteractWidget* TreeNodeCalendarW::getTitle() { return label_; }

void TreeNodeCalendarW::performAction(Action action) {}

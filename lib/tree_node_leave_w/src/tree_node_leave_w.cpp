#include "tree_node_leave_w.hpp"

#include <memory>

#include "tree_node_w.hpp"

TreeNodeLeaveW::TreeNodeLeaveW() {}

void TreeNodeLeaveW::checkNode() { check_box_->setChecked(true); }

void TreeNodeLeaveW::uncheckNode() { check_box_->setChecked(false); }

void TreeNodeLeaveW::showNode() {}

void TreeNodeLeaveW::closeNode() {}

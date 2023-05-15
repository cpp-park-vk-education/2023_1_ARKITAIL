#include "tree_node_leave_w.hpp"

#include <memory>

#include "tree_node_w.hpp"

TreeNodeLeaveW::TreeNodeLeaveW() {}

void TreeNodeLeaveW::checkNode() { check_box_->setChecked(true); }

void TreeNodeLeaveW::uncheckNode() { uncheckParentNodes(); }

void TreeNodeLeaveW::showNode() {}

void TreeNodeLeaveW::closeNode() {}

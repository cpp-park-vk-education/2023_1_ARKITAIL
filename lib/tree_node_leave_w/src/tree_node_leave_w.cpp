#include "tree_node_leave_w.hpp"

#include <memory>

#include "options_w.hpp"
#include "tree_node_w.hpp"

TreeNodeLeaveW::TreeNodeLeaveW() {}

void TreeNodeLeaveW::checkNode() { check_box_->setTristate(true); }

void TreeNodeLeaveW::uncheckNode() { check_box_->setTristate(false); }

void TreeNodeLeaveW::showNode() {}

void TreeNodeLeaveW::closeNode() {}

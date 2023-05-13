#pragma once

#include <Wt/WText.h>

#include "tree_node_leave_w.hpp"

class TreeNodeCalendarW : public TreeNodeLeaveW {
  public:
    TreeNodeCalendarW(int id, std::string label);
    ~TreeNodeCalendarW() = default;

  private:
    Wt::WText* label_;
};

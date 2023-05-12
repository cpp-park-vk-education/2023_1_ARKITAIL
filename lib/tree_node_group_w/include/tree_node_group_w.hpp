#pragma once

#include <Wt/WInPlaceEdit.h>

#include "options_w.hpp"
#include "tree_node_leave_w.hpp"

class TreeNodeGroupW : public TreeNodeLeaveW {
  public:
    TreeNodeGroupW(std::string label);
    ~TreeNodeGroupW() = default;

  private:
    Wt::WInPlaceEdit* label_;
};
